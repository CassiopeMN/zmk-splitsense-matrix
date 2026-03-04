#include <zephyr/kernel.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#define SPLITSENSE_SERVICE_UUID \
    BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef0))

#define SPLITSENSE_MATRIX_CHAR_UUID \
    BT_UUID_DECLARE_128(BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abcdef1))

// 2 bytes:
// [0] is_pressed (1 or 0)
// [1] position (0-255)
static uint8_t matrix_payload[2];

static void splitsense_matrix_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value) {
    bool notif_enabled = (value == BT_GATT_CCC_NOTIFY);
    LOG_INF("SplitSense Matrix Notifications %s", notif_enabled ? "enabled" : "disabled");
}

BT_GATT_SERVICE_DEFINE(splitsense_matrix_svc,
    BT_GATT_PRIMARY_SERVICE(SPLITSENSE_SERVICE_UUID),
    BT_GATT_CHARACTERISTIC(SPLITSENSE_MATRIX_CHAR_UUID, BT_GATT_CHRC_NOTIFY,
                           BT_GATT_PERM_NONE, NULL, NULL, NULL),
    BT_GATT_CCC(splitsense_matrix_ccc_cfg_changed,
                BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);

// Event listener for matrix positions
static int splitsense_matrix_event_listener(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);
    if (ev == NULL) {
        return 0; // Not a position event
    }

    // Pack the payload
    matrix_payload[0] = ev->state ? 1 : 0;
    matrix_payload[1] = (uint8_t)(ev->position & 0xFF);

    LOG_DBG("SplitSense Matrix: position %d, state %d", ev->position, ev->state);

    // Notify connected client
    int err = bt_gatt_notify(NULL, &splitsense_matrix_svc.attrs[1], matrix_payload, sizeof(matrix_payload));
    if (err && err != -ENOTCONN) {
        LOG_WRN("SplitSense Matrix notify failed (err %d)", err);
    }

    return 0;
}

ZMK_LISTENER(splitsense_matrix, splitsense_matrix_event_listener);
ZMK_SUBSCRIPTION(splitsense_matrix, zmk_position_state_changed);
