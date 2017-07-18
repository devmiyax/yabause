#ifndef PLATFORM_GLFW_H
#define PLATFORM_GLFW_H

#ifdef PLATFORM_LINUX
#error "A platform has already been set"
#else
#define PLATFORM_LINUX
#endif

extern int platform_SetupOpenGL(int w, int h);
extern int platform_YuiRevokeOGLOnThisThread();
extern int platform_YuiUseOGLOnThisThread();
extern void platform_swapBuffers(void);
extern int platform_shouldClose();
extern void platform_Close();
extern int platform_Deinit(void);
extern void platform_HandleEvent();

#endif
