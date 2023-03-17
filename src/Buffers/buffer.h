#pragma once

#include <GL/glew.h>

namespace Graphics {

	class Buffer
	{
	private:
		GLuint bufferID;
		GLuint componentCount;
	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componentcount)
			: componentCount(componentcount)
		{
			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ARRAY_BUFFER, bufferID);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void bind() const { glBindBuffer(GL_ARRAY_BUFFER, bufferID); }
		void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		inline GLuint getComponentCount() const { return componentCount; }
	};

}