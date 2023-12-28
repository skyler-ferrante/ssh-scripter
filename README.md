# SSH Scripter

Script SSH commands based on config files.
Can be used to brute force SSH credentials and then run commands.

Requires libssh-dev: `sudo apt-get install libssh-dev`

Build: `make`

Usage `./ssh-runner #With config files in config/`

Usage `./ssh-runner hosts_file username_file password_file commands_file`

Create config files:
```
mkdir config
echo example.com > config/hosts
echo user1 > config/usernames
echo user2 >> config/usernames
echo password1 > config/passwords
echo ls > config/commands
```

Config files are newline separated.
