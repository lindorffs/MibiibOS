# MibiibOS - V 1.1.5
## A research kernel and quasi-operating system
### WARNING: DANGEROUS AT BEST.

A BIOS Capable, kernel, operating system and shell designed as a basis for reserach into operating system and kernel development. Does a lot of things wrong. Probably all of them.

Credit due to Pritam Zopes for introducing me to the world of Kernels.

# Initial Boot:
Kernel Initiailization

Initial OS Boot (Username, Password, Hostname) (Note: Nothing needs to be entered. Blank values are accepted, and do not break things.)

Login Screen (If no username or password is set, press enter when prompted for those fields.)

Shell (See below.)

# Available Shell Commands:
To see the availalbe programs, enter "/help" in the shell prompt.

Available programs can be added by adding or changing the function pointers
and commands in "shell.c"

All commands listed below begin with /

## lock
runs os_lock() to prevent the system from being used.

## reinit
runs os_init()

## echo
runs echo_hook() as defined in echo.c

## free
displays current count of memory allocations, and bytes allocated to previous mallocs();

## edit
edits bytes displayed using "/free"

## view
displays bytes in a fancier way than "/free"

## create
creates an allocation of memory for use in "/edit" and "/view"

## env
allows changing of TTY foreground color.

## clear
clears (reinitializes) the TTY
