#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <linux/joystick.h>

#ifdef __cplusplus

class Joystick
{
protected:
    char *device;
    int js_fd;
    int axis_count;
    int button_count;
    char name[80];
    int *axes;
    char *buttons;
    struct js_event event;

public:
    Joystick();
    Joystick( const char* joydev );
    int init( const char* joydev );
    void stop();
    char getButton( int button );
    int getAxis( int axis );
    char* getName();
    char* getDevice();
    int numAxes();
    int numButtons();
    int connected;
};

#else

typedef struct
{
    char *device;
    int js_fd;
    int axis_count;
    int button_count;
    char name[80];
    int *axes;
    char *buttons;
    struct js_event event;
} Joystick ;

Joystick* js_open ( const char* joydev );

char getJSButton( Joystick* js, int button );

int getJSAxis( Joystick* js, int axis );

void js_close( Joystick* js );

#endif // JOYSTICK_H
#endif // JOYSTICK_H
