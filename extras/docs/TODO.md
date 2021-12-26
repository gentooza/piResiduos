#GENERAL
##ERRORES
+ (1804031145) En salidas de producto, al realizar una salida de transito de una orden, e introducir un vehiculo nuevo para esa orden, se salta el estado de introducir matricula justo despues de pulsar Forzar autorizacion de producto, y nos lleva al estado de introducir peso. Una vez introducido el peso, podemos proceder a introducirlo a transito aun teniendo una matricula vacia. **hay que investigarlo más**
###LOGICA
+ (1803281200) qué hacemos si al salvar un movimiento no tenemos acceso con el servidor remoto? Ahora mismo no hacemos nada!
###BASE DE DATOS
###GUI
+ (1802261400) la selección de peligroso o no peligroso en mask6 no puede ser editable
+ (1707041400) animación de carga de peso por encima de su botón
+ (1801180900) animación de carga más centrada 
+ (180410AC) el mensaje de formulario cancelado debería ser "formulario reiniciado", "movimiento terminado" o algo por el estilo
###DI

##MEJORAS
###SOBRE LA TABLETA DE FIRMAS
+ (1803261000) pruebas con la tableta nueva signotec
+ (1707061141) mejorar el aspecto de la firma resultante, seguir trazo y pixeles redondos no cuadrados (y un poco más pequeños)
###SOBRE LAS INCIDENCIAS
###GUI
+ (1707191107) mostrar precio cuando es un cliente particular
+ (1707191113) pago al contado, para clientes particulares u otros. mostrar precio, y almacenar cantidad pagada
+ (1801261400) trabajo con convoys, como lo gestionamos? remolques, etc.
+ (1802090900) puede ser que una matrícula registrada entre con un cliente que no tiene relacionado. El sistema ahora mismo no lo permite. Dar la opción siempre de un cliente "otros" que luego se pueda editar manualmente en la edición del DI.
+ (1802231130) si creamos una transferencia con un vehículo que SI está registrado en el sistema, a la entrada de este nos debe de dejar asociarlo a un cliente o tratarlo como una transferencia. (como se gestiona?)
+ (1802141100) con el planteamiento actual el operario de salida de las transferencias, puede poner una matrícula/código a mano de su elección. Podría equivocarse, no hay forma de ver las transferencias perdidas, corregirlas o borrarlas llegado el caso. Solución?
+ (1802221200) cuando pulsamos test firma se pone a copiar la firma en blanco, y eso tarda, habría que animar el estado con la animación de carga
+ (1892221256) al sacar de transito creamos el DI de nuevo al vuelo, deberíamos de tenerlo en cuenta a la hora de borrar el vehículo de tránsito ya que un cambio en ese momento ene l cliente, su NIF o algo, afectaría luego al borrado y actualización del camión.
####CONFIGURACIÓN
###DATABASE
+ (1802261145) revisión base de datos sqlite, su creación dinámica por programa si no existe, campos borrado en tablas, script de contrucción... etc.
###SOBRE EL DI

##WEB
+ al insertar nuevo producto nombre1 es indispensable, nombre2 y nombre3 son opcionales.
+ la hora del servidor no es la correcta, las fechas creadas están mal (por ejemplo en órdenes)
+ hay registro con la codificación de caracteres mal en la abse de datos, UTF-8?
+ Se pueden introducir matrículas con letras en minúscula, lo que puede generarnos futuros problemas. El programa compara siempre con mayúsculas, y guardará los datos en la base de datos con mayúsculas. 
+ En creacion de cliente nuevo, si alguno de los campos no cumple requisito (Por ejemplo NIF mas corto de lo esperado) se resetea el formulario entero. Podrian guardarse los campos en edicion y no borrarse hasta finalizarlo? 


# QUE DEBEMOS TENER EN CUENTA CUANDO CODIFIQUEMOS UN ESTADO:
+ su apariencia
+ su foco, para que con teclado se pueda trabajar
+ el código de retorno cuando venimos de otra pantalla y recuperamos el formulario
+ tenemos que tener la posibilidad de escribir comentarios!
+ cambio de entrada a salida de planta (tanto en entrega como recogida) no implementado!
