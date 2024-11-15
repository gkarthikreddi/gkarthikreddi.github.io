+++
title = "Fixing Unverified Git Commits"
date = "2023-07-16"
description = "A note to myself"
+++ 

If you are getting unverified tag in your github account when you commit using ssh from your local machine, then following instructions might help. Firstly check if you have `.gitconfig` file in your home directory. If you don't have it you need to create one. You can do it terminal using the below command.
```bash
touch $HOME/.gitconfig
```
After creating the file, you need to add your signinkey and email to your `.gitconfig`. You can do that in one of two way:
1. Through terminal
2. Editing the `.gitconfig` file

### Through terminal
- Add your public SSH key to the signinkey, make sure that you use the same key that you use for your github account. Replace *SSH_KEY* with your pubic key
```sh
git config user.signinkey = YOUR_SSH_PUBLIC_KEY
```
- Add your email as well
```sh
git config user.signinkey = EMAIL
```

### Edit the `.gitconfig` file
Paste the following content and replace YOUR_NAME, YOUR_EMAIL and SSH_KEY.
```bash
# .gitconfig
[user]
email = YOUR_EMAIL
name = YOUR_NAME
signingkey = SSH_KEY
```
Confirm that you added both *signinkey* and *email* by entering the below command in the terminal. This command will the contents of your `.gitconfig`.
```bash
git config --list
```
You are good to go
