#!/bin/bash

#	Author: Michael Weaver
#	Course: CST - 221
#	University: GCU
#	Instructor: John Zupan

#	Description: This assignment adds users to the system from a file, creating respective home
#		directories as they are created. Deleting a user, deletes their home directory.

#	Run this method with (./user_management.sh users.txt) from the terminal

# 	while IFS='' read -r line || [[ -n "$line" ]]; do
#		echo "Text read from file: $line"
# 	done < "$1"

#	Encrypt a string: echo -n "aaaabbbbccccdddd" | openssl enc -e -aes-256-cbc -a -salt

#	run this file from the containing directory with (./user_management.sh)

group="testGroup"
if grep -q $group /etc/group
then
     echo "group exists"
else
     groupadd $group
fi

filename="users.txt"
while read -r username password
do
    	name="$username"
	pass="$password"
	echo "Username: $name"
	echo "Password: $pass"
    	if [ $(id -u) -eq 0 ]; then
		egrep "^$name" /etc/passwd >/dev/null
		if [ $? -eq 0 ]; then
			echo "$name exists!"
			exit 1
		else
			useradd -m -p $pass $name
			[ $? -eq 0 ] && echo "User has been added to 	system!" || echo "Failed to add a user!"
		fi
	else
		echo "Only root may add a user to the system"
		exit 2
	fi
	usermod -aG $group $name
done < "$filename"

filename="users.txt"
while read -r username password
do
	name="$username"
	pass="$password"
	userdel -r $name
	echo "User Deleted."
done < "$filename"

if grep -q $group /etc/group
then
	groupdel $group
else
     	echo "Group does not exist."
fi
