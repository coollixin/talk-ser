#!/bin/bash

echo "please input you email:"
read email

str=`echo $email | gawk ‘/^([a-zA-Z0-9_\-\.\+]+)@([a-zA-Z0-9_\-\.]+)\.([a-zA-Z]{2,5})$/{print $0}‘`
if [ ! -n "${str}" ]
then
            echo "validation is wrong."
        else
                    echo "Your eamil is: ${str}"
                fi
