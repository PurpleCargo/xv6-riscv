# Informe Tarea 0 - Sistemas Operativos, Sec. 1
### Nombre: Eduardo Torres Lagos
### Sistema: Windows 11, WSL2, Ubuntu 22.04.3 LTS

## Pasos de instalación

1. Crear fork del repositorio xv6-riscv y clonarlo en /home/
	git clone https://github.com/PurpleCargo/xv6-riscv.git
2. Clonar repositorio riscv-gnu-toolchain en /home/ y navegar al directorio del toolchain
	git clone https://github.com/riscv/riscv-gnu-toolchain && cd riscv-gnu-toolchain
3. Ejecutar el comando de instalación de dependencias que aparece en el readme del repositorio del toolchain
	sudo apt-get install autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev
	libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev
	ninja-build git cmake libglib2.0-dev libslirp-dev
3.1 Ejecutar el siguiente comando antes del anterior si es que hace falta:
	sudo apt-get update
4. Ejecutar el comando de configuración para instalar en /home/riscv
	./configure --prefix=$HOME/riscv
5. Ejecutar comando de compilación/build, agrego -j4 para acelerar un poco la instalación, pero es opcional
	make -j4
6. Actualizar path con el toolchain (el segundo comando es opcional si no me equivoco, dado que vuelve el cambio
de path permanente para no tener que ejecutarlo entre sesiones de terminal y reboots)
	export PATH=$HOME/riscv/bin:$PATH
	source ~/.bashrc
7. Instalación de QEMU
7.1 Clonar repositorio de QEMU en /home/ y navegar al directorio qemu
	git clone https://github.com/qemu/qemu.git
	cd qemu
7.2 Configurar la instalación de QEMU para riscv
	./configure --target-list=riscv64-softmmu
7.2.1 En caso de que haga falta, instalar tomli
	pip install tomli
7.3 Ejecutar los siguientes comandos
	make
	sudo make install
8. Ahora toca navegar al directorio xv6-riscv
	cd -- && cd xv6-riscv
Editar el Makefile para añadir la siguiente línea:
	QEMUOPTS += -display none -serial mon:stdio
Con el fin de asegurarse que todo el output sea dirigido al terminal
9. Ejecutar los siguientes comandos para terminar la instalación
	make
	make qemu
9.1 En caso de que haga falta por x razón, ejecutar make clean antes de make

## Problemas encontrados
1. El mayor problema que tuve francamente fue con QEMU, dado que probé tres versiones distintas de instalación:
	sudo apt-get install qemu
Esta instalación si no me equivoco me resultaba en que make qemu efectivamente se ejecutaba, pero no aparecía la
interfaz en la terminal. La solución que intenté después de esto fue instalar otra versión de qemu que fuera
compatible con riscv.
	sudo apt-get install qemu-system-misc
Esta instalación me llevo al mismo problema en el paso de make qemu (aunque en ambas ocasiones no utilicé los mismos
pasos que mencioné más arriba en el documento, dado que para esta segunda instalación empecé de 0 esencialmente)

La solución que me resolvió el problema fue primero desinstalar ambas versiones de qemu y eliminar cualquier archivo
residual, seguido de compilar qemu como explico en los pasos de instalación.

2. Más que un problema esto esencialmente me pasó por intentar llegar con todo listo a la clase donde tuvimos el
laboratorio de xv6, dado que tuve que eliminar todo el progreso que llevaba (hasta el punto de make qemu sin
interfaz) para seguir los pasos en clase, con el tema de github y todo eso.

2.1 Además de eso, hubo un punto entre la primera y segunda instalación de qemu donde intenté instalar el toolchain
en /opt/ el cual requiere permisos para escribir, por lo que tuve que borrar la compilación del toolchain e
instalarlo de nuevo en /home/.

### Evidencia de que xv6 funciona correctamente
En el buzón de entrega de webcursos adjunto capturas de los comandos ls, echo y cat de acuerdo a las instrucciones
de la tarea 0
