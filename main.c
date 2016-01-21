#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <sys/utsname.h>

bool IsRunning = true;

static void handleEvent(Display *dpy, int s, Window mainwindow, Atom atom, bool uname_ok, struct utsname sname, XEvent *e)
{
  switch (e->type)
  {
    case Expose:
      {
        int y_offset = 20;

        const char* s1 = "X11 test app under Linux";
        const char* s2 = "by thekyz";

        XSetForeground(dpy, DefaultGC(dpy, s), 0xffffff);

        XDrawString(dpy, mainwindow, DefaultGC(dpy, s), 10, y_offset, s1, strlen(s1));
        y_offset += 20;
        XDrawString(dpy, mainwindow, DefaultGC(dpy, s), 10, y_offset, s2, strlen(s2));
        y_offset += 20;

        if (uname_ok)
        {
          char buf[256] = {0};
          
          sprintf(buf, "System information:");
          XDrawString(dpy, mainwindow, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
          y_offset += 15;

          sprintf(buf, "- System: %s", sname.sysname);
          XDrawString(dpy, mainwindow, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
          y_offset += 15;

          sprintf(buf, "- Release: %s", sname.release);
          XDrawString(dpy, mainwindow, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
          y_offset += 15;

          sprintf(buf, "- Version: %s", sname.version);
          XDrawString(dpy, mainwindow, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
          y_offset += 15;
          
          sprintf(buf, "- Machine: %s", sname.machine);
          XDrawString(dpy, mainwindow, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
          y_offset += 20;
        }


        XWindowAttributes  wa;
        XGetWindowAttributes(dpy, mainwindow, &wa);
        int width = wa.width;
        int height = wa.height;
        char buf[128]={0};
        sprintf(buf, "Current window size: %dx%d", width, height);
        XDrawString(dpy, mainwindow, DefaultGC(dpy, s), 10, y_offset, buf, strlen(buf));
        y_offset += 20;
      }
      break;

    case KeyPress:
      {
        char buf[128] = {0};
        KeySym keysym;
        int len = XLookupString(&e->xkey, buf, sizeof buf, &keysym, NULL);
        if (keysym == XK_Escape)
        {
          IsRunning = false;
          break;
        }
      }
      break;

    case ClientMessage:
      if ((int)(e->xclient.data.l[0]) == atom)
      {
        IsRunning = false;
      }
      break;

    default:
      // Do nothing ...
      break;
  }
}
 
int main(int argc, char** argv)
{
  Display* dpy = XOpenDisplay(NULL);
  if (dpy == NULL) 
  {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }
 
  int s = DefaultScreen(dpy);
  Window mainwindow = XCreateSimpleWindow(dpy, RootWindow(dpy, s), 10, 10, 800, 600, 1, BlackPixel(dpy, s), BlackPixel(dpy, s));
  XSelectInput(dpy, mainwindow, ExposureMask | KeyPressMask);
  XMapWindow(dpy, mainwindow);
 
  XStoreName(dpy, mainwindow, "X11 window");

  Atom WM_DELETE_WINDOW = XInternAtom(dpy, "WM_DELETE_WINDOW", False); 
  XSetWMProtocols(dpy, mainwindow, &WM_DELETE_WINDOW, 1);  
 
  bool uname_ok = false;
  struct utsname sname;  
  int ret = uname(&sname);
  if (ret != -1)
  {
    uname_ok = true;
  }
 
  XEvent e;
  while (IsRunning) 
  {
    // XNextEvent(dpy, &e);
    if (XCheckMaskEvent(dpy, ~NoEventMask, &e))
    {
      handleEvent(dpy, s, mainwindow, WM_DELETE_WINDOW, uname_ok, sname, &e);
    }
  }
  
  XDestroyWindow(dpy, mainwindow);
  XCloseDisplay(dpy);
  return 0;
}