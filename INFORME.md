# Informe Tarea 1 - Sistemas Operativos, Sec. 1
### Nombre: Eduardo Torres Lagos
### Sistema: Windows 11, WSL2, Ubuntu 22.04.3 LTS


## Ignorar este archivo, corresponde a tarea 1

## Funcionamiento de las llamadas al sistema

1. getppid()


	```
	struct proc *p = myproc();
	if (p->parent) {
		return p->parent->pid;
	}
	return 0;
	```

La función recupera el proceso actual myproc(), luego accede al proceso padre y retorna el id del proceso padre.


2. getancestor()


	```
	int gen;
  	argint(0, &gen);

  	if (gen < 0) {
    		return -1;
  	}

  	struct proc *p = myproc();

  	for (int i = 0; i < gen; i++) {
    		if (p->parent == 0) {
      			return -1;
    		}
    		p = p->parent;
  	}

  	return p->pid;
	```


Esta función utiliza la función argint para recuperar el valor de input asignado a la variable gen, luego evalua si
gen es un valor inválido de generación en el árbol de procesos. Luego declara un puntero a myproc() para utilizarlo
en el for que itera por cada generación de procesos, retornando -1 cuando no hay más ancestros. Finalmente la función
retorna el id del proceso del ancestro.


## Explicación de las modificaciones realizadas

1. user.h

Aquí agregué las declaraciones de las funciones getppid y getancestor.


2. proc.c

Aquí agregué la implementación de las funciones getppid y getancestor.


3. syscall.h

Aquí agregué las definiciones de las funciones getppid y getancestor.


4. syscall.c

Aquí establecí el mapping de las funciones getppid y getancestor.


5. usys.pl

Aquí agregué las llamadas de sistema creadas para que se incluya la referencia al generar el archivo usys.S
utilizando este script, o al menos eso entendí.


6. Makefile

Aquí agregué el programa de prueba 'yosoytupadre.c' a UPROGS y una regla de compilación para el programa


	```
	$U/_yosoytupadre: $U/yosoytupadre.o $(ULIB)
    	$(LD) $(LDFLAGS) -T $U/user.ld -o $U/_yosoytupadre $U/yosoytupadre.o $(ULIB)
    	$(OBJDUMP) -S $U/_yosoytupadre > $U/yosoytupadre.asm
	```


para asegurarme de que se compile correctamente. Esta regla enlaza los object files y crea un ejecutable, y objdump
desmonta el binary generado en código assembly con fines de debugging


## Problemas encontrados

1. El primer error que tuve fue que cuando estaba realizando las modificaciones para implementar getppid, había
una disparidad por así decirlo de tipos, dado que estaba utilizando int en lugar de uint64, y según entendí xv6
tiende a utilizar el tipo uint64, por lo que al cambiar los int por uint64 se resolvió el problema.

2. El segundo error, probablemente el mayor que tuve, fue que al compilar xv6 me saltaba el error de 
undefined reference to getppid, y esto se debía a que no había modificado el archivo usys.S, y cuando lo modificaba
e intentaba compilar otra vez, seguía teniendo el mismo error. Luego de estudiar un poco la estructura de los
archivos de xv6 noté que había un archivo llamado usys.pl el cual generaba el archivo usys.S al compilar, por lo que
al implementar la línea


	`entry("getppid")`


se resolvió el problema de referencia, y xv6 pudo compilar correctamente.

3. El siguiente problema lo noté tras ejecutar xv6 usando make qemu. Al parecer el executable de yosoytupadre.c
fallaba, y el problema estaba en que me faltaba una regla de compilación para el programa de prueba (la cual está
más arriba), por lo que al agregar esta regla en el Makefile abajo de la regla de forktest se solucionó.

4. Cuando estaba implementando la función getancestor en proc.c, al compilar tenía un problema relacionado a la
función argint, dado que me estaba retornando void en lugar del int que pudiera evaluarse con 0, por lo que en vez
de intentar evaluar el valor retornado llamé a la función directamente, lo que resolvió este problema.
