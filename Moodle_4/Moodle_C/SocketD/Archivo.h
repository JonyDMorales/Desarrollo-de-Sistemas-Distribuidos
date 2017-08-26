#ifndef ARCHIVO_H_
#define ARCHIVO_H_

class Archivo{
	public:
 		Archivo(const char *filename);
 		Archivo(const char *filename, mode_t modo);
 		~Archivo();
 		size_t lee(size_t nbytes);
 		size_t escribe(const void *buffer, size_t nbytes);
 		char* get_contenido();
 		void cerrar();
	protected:
 		string nombreArchivo; //Almacena el nombre del archivo
 		int fd; //Almacena el descriptor de archivo
 		char* contenido; //Almacena temporalmente contenido parcial o total del archivo
}; 

#endif