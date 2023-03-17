#pragma once

#include <GL/glew.h>

namespace Graphics {

	class IndexBuffer
	{
	private:
		GLuint bufferID;
		GLuint count;
	public:
		IndexBuffer(GLushort* data, GLsizei count)
			: count(count)
		{
			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID); }
		void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline GLuint getCount() const { return count; }
	};

}