#ifndef texture_h
#define texture_h

GLuint createTexture(int width, int height);
void cleanTexture(GLuint texture);

void bindImageTexture(GLuint texture, int slot);
void bindSampleTexture(GLuint texture, int slot);

#endif