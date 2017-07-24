#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <linux/input.h>
#include "joystick.h"

Joystick::Joystick()
{
    connected = 0;
    axis_count = 0;
    button_count = 0;
}

Joystick::Joystick( const char* joydev )
{
    if( init( joydev ) < 0 )
        connected = 0;
}

int Joystick::init( const char* joydev )
{
    connected = 0;
    axis_count = 0;
    button_count = 0;
    js_fd = open( joydev, O_RDONLY );

    if( js_fd < 0 )
        return -1;

    device = strdup( joydev );
    ioctl(js_fd, JSIOCGAXES, &axis_count);
    ioctl(js_fd, JSIOCGBUTTONS, &button_count);
    ioctl(js_fd, JSIOCGNAME(80), &name);
    axes = (int*) malloc(axis_count * sizeof(int));
    buttons = (char*) malloc(button_count * sizeof(char));
    fcntl(js_fd, F_SETFL, O_NONBLOCK);
    connected = 1;
    return 0;
}

void Joystick::stop()
{
    if(connected)
    {
        close(js_fd);
        connected = 0;
        free(axes);
        free(buttons);
    }
}

char Joystick::getButton( int button )
{
    int res = read(js_fd, &event, sizeof(struct js_event)); res = 0;

    switch ((event.type) & ~JS_EVENT_INIT)
    {
        case JS_EVENT_AXIS: (axes)[event.number] = event.value;
            break;
        case JS_EVENT_BUTTON: (buttons)[event.number] = event.value;
            break;
    }

    if(button <= (button_count))
         return (buttons)[button];

    return -1;
}

int Joystick::getAxis( int axis )
{
    int res = read(js_fd, &event, sizeof(struct js_event)); res = 0;
    switch ((event.type) & ~JS_EVENT_INIT)
    {
        case JS_EVENT_AXIS: (axes)[event.number] = event.value;
            break;
        case JS_EVENT_BUTTON: (buttons)[event.number] = event.value;
            break;
    }

    if(axis <= axis_count)
        return (axes)[axis];

    return -65535;
}

char* Joystick::getName()
{
    return (char*) name;
}

char* Joystick::getDevice()
{
    return device;
}

int Joystick::numButtons()
{
    return button_count;
}

int Joystick::numAxes()
{
    return axis_count;
}
