#pragma once 

#include "../../include/GL/glew.h"

class Buffer {
    private:
        GLuint BufferID
        GLuint ComponentCount;
    public:
        VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount) {
            
        };

        void bind() const {

        }

        void unbind() const {

        }
}