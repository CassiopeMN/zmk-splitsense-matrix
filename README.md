# ZMK Matrix Event Streamer Module

This module adds a custom BLE GATT service to any ZMK keyboard that broadcasts raw logical key positions (0-N) whenever a key is pressed or released.

## Setup Instructions

1.  In your `zmk-config` repository, open `config/west.yml`.
2.  Add this repository to your `remotes` and `projects`:

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: my-modules
      url-base: https://github.com/YOUR_GITHUB_USERNAME # Измени на свой
  projects:
    - name: zmk
      remote: zmkfirmware
      import: app/west.yml
    - name: zmk-splitsense-matrix
      remote: my-modules
      revision: main
```

3.  In your `config/lily58.conf` (или `config/lily58_left.conf`), add:

```properties
CONFIG_SPLITSENSE_MATRIX=y
```

4.  Commit and push to trigger the GitHub Actions build.
