#2019/05/09 version 0.1.6b
+ ERRORES:
    - arreglo bloqueo en último paso en desacargas de material, cuando no hay conexión con la base de datos central.

#2019/04/12 version 0.1.6
+ MEJORAS:
    - procedimiento de re-chequeo del guardado de un movimiento en entradas de material, para evitar posibles falsos positivos en cuanto a guardado y sincronizado.
    - insertado el tipo de movimiento D5 para cuando una entrada de material se produce en el depósito
    - para mantener un mismo tamaño de código de movimiento, el código estación tendrá ahora siempre 2 cifras, 01, 02...11..21..
    - una salida de transferencia y su psoterior entrada, no genera ya una incidencia por matŕicula insertada a mano.
+ ERRORES:
    - error al resetear el cliente volviendo del estado 20, en entradas de material.
    - En el DI impreso la tara y el bruto ya no aparecen intercambiados.
    - no mandamos ya más correos de incidencias cuando no las hay.

#2019/01/16 version 0.1.5
+ MEJORAS:
    - sincronización automática configurable en la pantalla de configuración.
    - código más estandarizado, mejor licenciado y organizado.
    - cuando la descarga de una transferencia falla en conexión con el servidor remoto, no finaliza y nos devuelve al estado anterior, así hasta que la conexión se restablezca. 
      Eso es para evitar incongruencias al no poder borrar la transferencia del servidor remoto.
+ ERRORES:
    - sincronización de transferencias corregida, para no sincronizar ya más las borradas en el servidor.
    - borrado de las transferencias realizadas corregido, ya no borramos transferencias que previamente habáin sido borradas en el servidor.
    - borrado de los vehículos en tránsito en salida de material arreglado.

# 2018/12/17 version 0.1.4b
+ MEJORAS:
    - DI más completo, con basculista, pesos, precio, comentario de operador, sello,  etc.
    - Transportes seleccionables mediante doble click de la tabla de tránsito
    - Nuevo sistema de logging de errores implementado para mejorar la depuración de fallos
    - La sincronización prioriza ahora los datos locales de tránsito de vehículos.
    - logging de basculista por código para terminar cualquier movimiento.
    - transportistas por defecto o seleccionado mostrados en la misma pantalla de entradas y salidas de material
    - los vehiculos en la base de datos ahora tienen 10 posibles clientes asociados, en vez de sólo 5.
+ ERRORES:
    - ya no sincronizamos más registros borrados previamente de clientes, productos, matrículas y transportistas
    - contraseña arreglada en la pantalla de configuración, ahora se ve como asteriscos.
    - clientes en estado 110 son mostrados alfabéticamente ahora en su menú desplegable
    - arreglos varios en el manejo de tránsito
    - quitados los botones residuales de sincronización en las pantallas de edición del DI.
    - las imagenes cargadas por las cámaras previamente se resetean y no aparecen al temrinar un movimiento.
    - la sincronización de archivos se ha arreglado, se daba el caso de borrar la carpeta antes de haber copiado los ficheros.
#2018/11/14 version 0.1.3
+ MEJORAS
    - ahora podemos elegir un cliente "otros" cuando es una descarga de material
+ ERRORES:
    - arreglo sincronizando las transferencias, ahora sincronizan bien.

#2018/11/07 version 0.1.2
+ MEJORAS
    - **sistema de sincronización mejorada**
    - sólo sicnronizamos ya el último movimiento en la estación
    - podemos ejecutar movimeintos sin sincronización, luego se sincronizan
    - ejecución de movimiento más rápida al sincronizar menos, y agilizar si hay conexión o no con el servidor remoto
    - base de datos local con bits de sincronización, sabemos ahroa qué movimientos originados en la estación han sido o no sincronizados ya
    - deshabiltiación de semáforos para agilizar la aplicación
    - la copia de archivos al servidor remoto se realiza de forma asíncrona ahora para agilizar el proceso
    - insertada tabla de basculistas y su entidad en código a falta de darle un uso definitivo
    - buffer de mensajes más corto para ahorrar memoria y agilizar la aplicación.
+ ERRORES:
    - arreglado que el botón de sincronizar nos e desactive a partir del estado 1231 en salida de planta, en descarga de material

#XXXX/XX/XX version 0.1
+ MEJORAS:
    - limpiamos el buffer de mensajes de información, sólo dejando los 6 últimos, para agilizar el sistema y liberar memoria cuando lleva mucho tiempo la aplicación funcionando
    - listado de transportistas en la edición del DI en orden alfabético

#2018/07/27 version 0.1 rc2
+ MEJORAS:
    - semáforos de cámaras incluidos en el control, se pueden configurar y se accionan automáticamente el entrar o salir transportes
    - sistema de cincidencias terminado, con mejor acabado en los mails e información.
+ ERRORES:
    - pequeños errores subsanados
    - túnel ssh se reconecta cada 4 horas, ahora, o si falla la sincronización.
#2018/05/25 version 0.0.95 BETHA
+ MEJORAS:
    - DI final más completo con el apartado 10 cumplimentado
    - Los comentarios de operador son salvados cuando se procede en el movimiento, ya no hace falta pulsar en el botón de "salvar" que es eliminado
    - la tabla de órdenes ahora muestra el LER bien definido.
    - los productos son mostrados ahora en sus comboboxes por orden alfabético
    - comboboxes de clientes y productos en mask4 más amplios
+ ERRORES:
    - los cajones de texto de pesos no son editables
    - código DI ahora generado correctamente de la forma: DI+CIF+AÑO+contador
#2018/05/15 version 0.0.94 BETHA
+ MEJORAS:
    - eliminación de la hora en la fecha inicial del movimiento, en edición del DI, y su impresión.
    - agregado el chequeo de conexión previo en las pruebas de cámaras de la pantalla de configuración.
    - animación de carga cuando se prueban cámaras y básculas en la pantalla de configuración.
    - economía de código y estandarización de las rutinas de uso de cámaras, todo el código está ya en mask_tools.h.
+ ERRORES:
    - toma de matrículas en entradas de material, estado 0, no funcionaba.
    - toma de matrícula en entrada a planta de salidas de material estaba mal configurada, usando la cámara 2 no la 3.
    - arreglo de pequeño fallo perdiendo la navegación en la pantalla de configuración, cuando se nos desactiva por carga de datos (sincronía, test cámaras, etc.)
#2018/04/26 version 0.0.93 BETHA
+ MEJORAS:
    - (1707191110ZZ) && (1802261000) sistema de incidencias implementado totalmente. (a falta de alguna producida en la edición del DI)
    - (1803140900) establecemos la impresora en .ini y pantalla de configuración
    - selección de nuestra identidad ahora en la pantalla de configuración
    - establecemos un porcentaje de error en la lectura de peso de las básculas de salida de planta en la salidas de material.
    - (1803261003) sería interesante mostrar los frames en rojo de datos que faltan por rellenar para dar el DI por válido
+ ERRORES:
    - (18042302) Al terminar la sincronización después de cambiar de estación, no se desbloquean los botones de Entrada / Salidas / Config.
    - (18042300) Al cambiar el correo para las incidencias “CC:(correo por linea)”,no se guarda al pulsar salvar (si saliamos y entrabamos de configuración aparecia de nuevo  jcuellar@prointegra.com).
    - (18041202) Las “T” en los tiempos aparecen cuando sincronizamos con la base de datos, pero ya han sido filtradas.
    - (18041703) Falta incidencia 001: matricula introducida a mano.
    - (18041701) No se guardan incidencias.
    - (18042405) No aparecian incidencias de salida de transito con el nuevo sistema de incidencias, para el primer movimiento. A partir del segundo movimiento, marcaba como incidencia de salida de transito la matrícula del movimiento anterior. En ningún caso aparecia la incidencia de peso de salida de transito introducido a mano.
    - (18042503) Se generaba la incidencia de peso correctamente al salir de transito, pero si retrocedia y vuelvia a introducir el peso, se quedaba guardada la primera incidencia.
    - (18042502) Arreglada incidencia de Peso en transito que ocasionaba clonaciones no deseadas de movimientos, con codigos de estacion 0.
    - (18040506) Tras introducir matricula quedaba basura (en la de salida de transito y salida de producto)
    - (18041109) En entrada de producto, si pulsamos Retroceder cuando tenemos el botón de Proceder en verde (estado 240), nos retrocede al estado 230, en vez de al 232. (Nos retrocede al estado de seleccionar producto en vez de al de introducir peso).
    - (18041901) En entrada de producto, al llegar al paso de elegir producto, hay basura en el cajetín de debajo del combobox si previamente hemos cancelado otra entrada de material y habíamos seleccionado producto permitido.
    - (18041902) En entrada de producto, al ir a configuración y volver en medio del proceso de entrada de un vehículo registrado, el circulo de Matricula registrada se queda en gris y no en verde.
    - (18042405) No aparecian incidencias de salida de transito con el nuevo sistema de incidencias.
    - (18042504) Al cambiar de estacion, falta sincronizar tabla de transferencia?
    - (18041903) Al ir a configuración y volver en medio del proceso de entrada de un vehículo registrado, parece que el simbolo de loading.gif bloquea los botones de “introducir peso a mano”, y el combobox de “seleccionar producto”
    - (18041909) Al introducir un cliente particular y forzar los permisos de su producto, se crea la carpeta correctamente con su DI y fecha, si pulso retroceder, no se borra (pudiendo elegir otro producto q crea otra carpeta).
    - (18042402) Si seleccionamos un cliente, al ir a configuracion y volver, perdemos la visualziación del cliente seleccionado. (El LineEdit que esta debajo del combobox siempre marca N/A, podria utilizarse)
    - (18041907) Al ir a configuración y volver en medio del proceso de entrada con vehiculo no registrado, se genera una nueva carpeta en saves (si voy y vuelvo 3 veces, se crean 3 carpetas distintas) si cancelo el movimiento solo se borra la ultima. Estado “132”
    - (18041906) Al ir a configuración y volver en medio del proceso de entrada de un particular, se pierde la visualizacion del producto que teniamos seleccionado

#2018/04/20 version 0.0.92 BETHA
+ MEJORAS:
    - (18040602) Salida de producto. Boton de Eliminar de transito implentado.
    - Añadido entorno gráfico para la selección de impresora.
+ ERRORES:
    - (18041101) Estamos en el estado 520 (introducir peso), si se pulsa retroceder nos lleva al estado 610 (forzar producto) en vez de al 510 (introducir matricula)
    - (18041106) Solucionado el perder el valor del comentario del operador en las salidas de producto si se cambiaba de pantalla.
    - (18040601) Al salir de la edicion del DI se bloquean los botones Entrada(F1) y Salida (F2) porque si pulsas muy rapido en Aceptar/Cancelar dentro del DI la aplicación se va a un estado incontrolado. De hecho ahora la interfaz posee un estado desactivado por defecto.
    - (18041103) Salida de producto. Orden. Al forzar producto, si retrocedemos (no cancelar) para seleccionar otra orden(que no necesite forzado), el forzado de la autorizacion se queda guardado y la incidencia apararece en la base de datos.
    - (18041104) Cuando ibamos a configuración y volviamos, los pilotos de los permisos se quedaban grises, ahora se muestran correctamente.
    - (18041102) bug ocasional que no nos permitia seguir en salida de producto tras introducir matricula.
    - (1804091300) implementar un destructor de la clase formulario
    - (180410AD) fallo en la sincronización de la tabla de tránsito salidas
    - (180410AE) fallo en la estructura de la tabla local de tránsito, arreglado el constructor bio.sqlite3
    - (18040506) quedaba absura en el cajón de editar matrícula en salidas de planta, de salida de material, una vez acabado un movimiento.
    - (18040510) Codigo origen y destino eran iguales en entrada de producto.
    - (18041110) Faltan los datos del cliente particular que han sido introducidos a mano
    - (18040503) Al cargar el DI aparecen los datos del DI anterior. Los campos deberían de empezar VACIOS siendo un particular
    - (18040602) Boton de Eliminar de transito funcional
    - (18041107) Faltaba incidencia de matricula introducida a mano en entradas de producto
    - (18041702) Corregido error de sincronizacion de la tabla de transferencias
    - (18041108) Los datos del apartado 5.a del DI no se guardaban al realizar transferencia (centro de origen)
    - (18040509) Las variables de pesos se almacenaban de forma errónea.
    - (18040604) Las transferencias finalizaban como movimiento tipo 1 y deberia ser tipo 2
    - (18040603) Faltaba incidencia de autorizacion de producto forzada
    - (18041704) Solucionado - Al editar el DI, en el apartado 6.a tenemos por defecto “Definido a mano” en el combobox, deberia de ser “Elija”
    - (18041705) Solucionado - Al editar DI apartado 6.a “Destino introducido a mano” no deja editar los campos
    - (18041807) Entrada de producto - Al pulsar cancelar no se borra la carpeta en Saves.
    - (18041801) Pesos Tara y Bruta cambiados de variable en entradas de producto.
    - (18041802) En salida de producto. Al terminar una transferencia, el combobox se queda marcado como “Transferencia” pero el terminal muestra que es como si estuviera en Movimiento desde transito ya que indica tipo de movimiento 3 en vez de 2
    - (18041904) Al finalizar una orden, se borra de la base de datos local, pero no de la web. Al sincronizar recuperamos la orden.
    - (18041301) Ordenes - salida de producto - Falta borrar orden al finalizar
    - (18042001) Corregido errata en el codigo de borrado de ordenes que causaba el borrado de la primera orden con opcion de Borrar=0.
    - (18041905) Transferencias - salida de producto - Al “retener transporte” no se borra la carpeta generada en save
    - (18041804) Transferencias - salida de producto - Se añade la firma con garabato al pulsar proceder
    - (18041805) Transferencias - salida de producto - Al proceder se genera el ticket en la carpeta, pero no se mueve a backup, se queda en saves.
    - (18042002) Solucionado pequeña errata en el frame 4 rojo que aparecia aun teniendo los campos con el cliente debidamente seleccionado.
    - (18041806) Salida de producto - ordenes - La carpeta no se genera (codigo en pestaña de CarpetaOrden) En el codigo aparece  Carpeta: “XXX” pero no estaba creada. Se crea al pulsar Test Firma
#2018/04/10 version 0.0.91 BETHA
+ MEJORAS:
    - codificación latina en escritura de PDF, ahora salen las tildes y ñs. **Requiere instalar de forma manual la versión nueva de la librería libhpdf**
    - **LA EDICIÓN E IMPRESIÓN DEL DI SE DA POR FINALIZADA**.
    - Añadido entorno gráfico para la selección de nuestra identidad (de cara al DI) en Configuración.
+ ERRORES:
    - (18040521)Falla visualizacion e impresion del DI en el apartado de centro de origen (5.a)  ¿Posible variable vacia?
    - (18040520) Corregido error en la impresión del peso en los formularios, variables corregidas en salida de producto.
    - salidas de transferencia reimplementadas
    - (1803271300) parece que no guardamos el peso en las salidas, volvemos a tránsito, y cuando cargamos no nos carga el peso en su cuadrante. (auqnue el camión está en verde, de estar pesado ya)
    - (1803231400) en entrada de material no parece que guardemos ninguna incidencia en la tabla movimientos, arreglada la pérdida del comentario del operador y de las incidencias registradas una vez editado el DI.
    - Ahora sí vemos el peso en entrada de material, cuando es un movimiento de transferencia
    - (18040505) Corregido que se mostrara la palabra "MATRICULA" en el campo de matricula de salida.
    - (18040525) Corregido el corte que se producia en la letra O de la palabra PESO.
    - (18040501)(18040502) visualización de los permisos a la entrada a planta corregida, había varios fallos
    - (1803221115) no se ve qué producto vamos a sacar en la entrada a planta de salida de materiales.
    - (1803231116)(18040514) nada más llegar al estado 520 no se nos permite editar un peso a mano (posiblemente la animación de carga esté encima del botón)
    - (18040518) solucionado - Se observa que si retenemos el vehículo una vez puesto su peso de salida, aunque aparece el icono en verde en la casilla de matriculas, no guarda el peso y tendremos que volver a introducirlo
    - (18040901) solucionado - Al pulsar Apartado 6 aparecen los valores correctos del cliente, pero si seleccionamos un centro de destino, salimos y volvemos a entrar en dicha pantalla perdemos el valor de las variables del cliente. Si por el contrario volvemos a seleccionar “Elija” o “Definido a mano” en el combobox, al salir de la pantalla y volver recuperamos los valores de las variables. 
    - Añadido DR como variable de visualizacion y de impresion.
    - (18040514) solucionado - No se puede editar el peso a mano si antes no se pulsa “Pesar” en la salida de producto.
    - (18040513) solucionado - Una vez forzados permisos del producto, aunq el foco pase a otro frame, sigue activa la parte de permisos.
    - (18040516) (18040603) solucionado - No aparece incidencia por forzar permisos en la salida de producto, tabla de transito y movimientos.
    - (180410AA) arreglo de fallos varios en la pantalla de configuración
#2018/04/04 version 0.0.9 BETHA
+ MEJORAS:
    - código limpiado alrededor de la clase central formulario.
    - estado 610 añadido, nuevo camino para producto con forzado de autorización en salida de productos
    - la identidad de bioreciclaje se configura ahora en el .ini, y es usada en la edición e impresión de Dis
    - mejoras sustanciales en la visualización del DI
    - mejoras sustanciales en la impresión del DI
    - la abse de datos ahora empieza a tener en cuenta los registros borrados (Se ha rediseñado)
+ ERRORES:
    - arreglos varios
    - (1803221000) quitar el carácter T residual en las fechas que vienen de mysql, caso de tabla de órdenes
    - (1803161201) la tabla de órdenes no se refresca una vez sinronizamos globalmente
    - (1803161200) revisar longitud de texto en la tabla de órdenes. si es muy larga peta. (quitar el nombre del producto por su ler)
    - (1803221300) el paso de editar DI da fallo de memoria, posible problema haciendo un deep copy de la clase formulario a la que vamos a usar para trabajar en la pantalla de edición del DI
    - fallo al poder aceptar matrículas en blanco almacenadas en tránsito
    - las tablas que tienen registro de borrado, pueden tener su valor sin inicializar! un registro válido es por tanto con BORRADO = 0 ó BORRADO IS null.
    - (1803221301) en entrada de producto, cuando sacamos un vehículod e tránsito. El peso no se muestra correctamente. Salidas de tránsito arregladas y simplificadas en general.
    - (1803261100) error cuando sacamos el NPT de un producto y cliente que cuya relación no está almacenada en la base de datos
    - (1803271400) error machacando el tipo de movimiento (salida, tránsito, órden, etc.) cuando sacamos un movimiento de tránsito
    - (1803280900) error escribiendo el PDF, fallo de memoria
    - (1804021400) varios errores salvando en tránsito de salida de material.
    - (1804021100) error en la gestión del tipo de movimiento, a veces nos guardaba tipo -1
    - (1802061140) deberíamos cargar todas las imágenes de la aplicación sólo una vez al inicio? es posible?
#XXXX/XX/XX version 0.0.8 dev
+ MEJORAS:
    - Sincronización de archivos de movimientos con el servidor central
    - impresora reimplementada. Ha venido para quedarse!
    - recuperamos los datos de nuestra estación de control, de la base de datos central
    - (1801171100) las estaciones ya no se van a configurar a mano, si no eligiendo las opciones presentes en la base de datos
+ ERRORES:
    - (1801241400) reejecución del túnel ssh si no lo tenemos! cuando detectamos fallo de conexión en la sincronización con la base de datos, reiniciamos el tunel ssh.
#2018/02/23 version 0.0.7 BETHA
+ MEJORAS:
    - (1801171200) implementar las salidas de transferencia y cotejarlo con el trabajo hecho ya en entradas de transferencia
    - transferencias completamente implementadas
    - (RODRIGO) pantallas de edición de DI planteadas gráficamente.
    - (1707251134) darle una repensada a los mensajes de información
+ ERRORES:
    - reseteamos datos una vez terminado un movimiento de descarga
    - arreglos de comportamiento de la interfaz, varios
    - (1707142116) todo estado de transacción (firma, pesaje, cámara...) debe deshabilitar cualquier botón que nos haga navegar, para evitar irnos a estados no controlados. **todo**
    - (1801091200) en estados de salida de planta, por ejemplo 1020 y 1021, y habrá más, aún se puede seleccionar entre camiones de la tabla tránsito, eso se debe de deshabilitar **carga y descarga, salida de planta**
#2018/02/15 version 0.0.6 BETHA
+ MEJORAS:
    - reimplementadas las cargas de material, con recepción de órdenes, etc. Y su almacenaje en movimientos.
+ MEJORAS IMPLEMENTADAS TOTALMENTE, TANTO EN ENTRADAS COMO SALIDAS
    - (1891241000) testear la conexión antes de intentar trabajar con elementos de red
        - (1801180901) sincronía sin conexión, probar, agilizar...
        - (1707191025) toma de matrícula con RED y sin cámara conectada, bloquea? Agilizamos?
    - (1712180900) añadir el uso de la cámara en salida de planta
    - (1801170900C) las pesadas han de poder ser editadas a mano, generando una incidencia.
    - (1801170901C) las matrículas han de poder ser editadas a mano, generando una incidencia.
+ ERRORES:
    - (1802080900) las cámaras retornan error cuando verdaderamente sí está conectada.
    - (1802080901) la cámara de salida de Descargas de material no muestra correctamente su imagen.
    - (1802081330) parece que en descargas de material, cuando tenemos camiones en tránsito y la aplicación cae, al retornar estos desaparecen
    - (1802091000) la tecla enter derecha no se detecta, ¡agregada la tecla derecha!

#2018/02/08 version 0.0.5 BETHA
+ MEJORAS:
    - sincronización con la base de datos central al inicio de descarga, tablas: tránsito y tránsito_salidas.
    - (1709061131) implementar teclas para todo, F1 -> pantalla de descargas, F2 -> pantalla de cargas, F3 -> pantalla de configuración, F5 -> cambio entre entrada/salida de planta (por ahora sólo en descarga y cargas de material. Falta la de configuración)
    - modificada la lógica de pesaje,firma y edición en la salida de camiones de planta, en entradas y salidas.
    - (1801180902) intercambiar posición botones retener firma y firmar.
    - (1801081300) establecemos un mecanismo para salvar la firma a la salida de un vehículo, de for que sepamos si ya se ha firmado el movimiento o no para que si el operador cambia de pantalla o retiene, al volver se pueda recuperar la firma que ya se había introducido y no haya que firmar de nuevo.
    - (1801170901C) las matrículas han de poder ser editadas a mano, generando una incidencia. (sólo entradas y salidas de descarga por ahora)
    - (1801170900C) las pesadas han de poder ser editadas a mano, generando una incidencia. (sólo entradas y salidas de descarga por ahora)
    - (1712180900) añadir el uso de la cámara en salida de planta (salidas de descarga de material)
+ ERRORES:
    - errores gráficos varios, vamos camino de dejar la interfaz y su comportamiento definitivo (entradas descarga por ahora)
    - (1711021100) las matrículas que se ingresan a mano deben permitir editarse aunque esté dentro de los parámetros definidos de corrección. (ahora mismo cambia de estado en cuanto tiene el tamaño X impidiendo su modificación para maś tamaño o correcciones **Arreglado con el nuevo sistema de entrada de datos por cuadro de texto**
    - (1891241000) testear la conexión antes de intentar trabajar con elementos de red (solo entradas descarga por ahora)
        - (1801180901) sincronía sin conexión, probar, agilizar...
        - (1707191025) toma de matrícula con RED y sin cámara conectada, bloquea? Agilizamos?
    - (1707061139) la aplicación cae cuando intentamos firmar y no hay una tableta de firmas conectada // qué hacer si no hay una tableta de firmas!? Mensaje de error si no hay tableta conectada

#2018/01/16 version 0.0.45 BETHA
+ MEJORAS:
    - sincronización con la base de datos central al inicio de descarga, tablas: clientes, productos, clientes-productos, vehiculos ,órdenes y movimientos.
    - DI se puede imprimir en la impresora brother HLL2360DN
    - (1711091124) No vamos a dejar cambiar de entrada a planta a salida a planta con un formulario abierto.
    - Animación de carga cuando sincronía (en pantalla de descarga)
    - (1707071057) mostrar algún tipo de animación de que el sistema está pensando cuando estamos salvando la firma, creando el pdf, etc.
    - Trabajos en agilización de la tableta de firmas
    - (1711081000) Retirar botones de reset pesada, no hacen falta y simplificaría la aplicación
    - (1711131100) codigo de estacion, configurable, pueste en el .ini.
    - (1711271343) quitar botón de puenteo de la firma, no es necesario ya!
    - (1712051100) quitar pantallas que no van, y limpiar código
    - (1801080900) resolución definitiva establecida, cuadro de información inferior, y logos redimensionados acorde.
    - (1710311120C) Pantalla para modificar a mano el DI, antes de imprimirlo **parcial**
        - (1711161000C) selector de transportista al terminar el movimiento y firmar **parcial**
    - (1801160800) los movimientos en entrada de material son sincronizados en la base de datos central
    - (1801160801) mecanismo por el que el DI debe de considerarse completo para terminar un movimiento de descarga **parcial**
+ ERRORES:
    - (1711211704) arreglo de camino 5 entradas PT con nueva base de datos
    - varios arreglos gráficos, coherencia de la interfaz, pantalla completa, etc.

#2017/11/24 version 0.0.4 BETHA (versión en planta)
+ MEJORAS:
    - generación del DI consultando la base de datos
    - implementada nueva base de datos, fecha 17/11/14
    - implementada la salida de vehículos de recogida de material
    - implementada una llegada *normal* de vehículo a recogida de material
    - CAMINO 6 IMPLEMENTADO, llegada de transferencias internas
    - implementar estación PT y ET en paralelo, trabajamos en PT
    - simplificación, PT y ET son iguales en pantallas, la búsqueda de datos es lo únicoq ue cambiará según ET/PT
    - nueva estructura de formulario, que case todos los movimientos posibles y tanto de entrada como salida a planta. De forma más clara, replicable y modificable
    - actualizada la librería de control de la tableta WACOM, no sabemos aún si arregla los problemas de estabilidad.
+ ERRORES:
    - (1710170900) las etiquetas que son informativas que no traigan texto por defecto, que en la transición de pantallas se ve siempre y es feo. (caso de título de pantallas)
    - (1711211700) arreglo de camino 1 entradas PT con nueva base de datos
    - (1711211701) arreglo de camino 2 entradas PT con nueva base de datos
    - (1711211702) arreglo de camino 3 entradas PT con nueva base de datos
    - (1711211703) arreglo de camino 4 entradas PT con nueva base de datos
    - (1711211705) arreglo de salida de descargar en entradas PT con nueva base de datos
    - (1711241000) arreglo de fallo de memoria al volver a estado 1100 salidas PT, desde otro formulario
    - (1711231200) cuando creamos un formulario parece contener información residual, asegurarnos que es 0
    - (1711211800) salir y retornar a entradas PT recuperando el formulario se ha roto, hay que arreglarlo
    - (1707141230) la tablet se queda pillada si intentamos una segunda firma, no está estable en general. Nos recuepramos del error y podemos firmar sin problema ya!

#2017/10/03 version 0.0.35 BETHA (versión de desarrollo)
+ MEJORAS:
    - (1706301200) sacar info por tableta de firmas. (Faltaría definir qué información sacamos)
    - (1706301159) mostrar la fecha y hora del sistema
    - (1709151000) se han implementado funciones para una programación más genérica, y se ha economizado código.
    - CAMINO 3 IMPLEMENTADO
    - CAMINO 4 IMPLEMENTADO
    - CAMINO 5 IMPLEMENTADO
    - (1707191020) las incidencias se almacenarán en la base de datos de movimientos
    - (1707191110Z) envío básico por correo de las incidencias, parámetros configurables
    - (1707191110ZZZ) configuración para correo de incidencias editable desde su pantalla
+ ERRORES:
    - (1709201100) MOSTRAR TODOS se presenta como segunda opción en su combobox, no al final, para un mejor acceso
    - varios errores estéticos subsanados
#2017/09/12 version 0.0.34 BETHA (versión en planta)
+ MEJORAS:
    - (1709050948C) comboboxes ahora navegables por teclado y seleccionables mediante la tecla ENTER
    - (1709050952C) en dichas tablas que aparezca el LER primero, antes del nombre del producto
    - (1709061130) por teclado deberíamos poder pesar para continuar con al filosofía de "todo" por teclado, practicamente hecho, lo que falte será tratado como fallos puntuales
    - (1709050935C) añadir un campo de comentario editable por el operario en los movimientos, que se almacene en la base de datos
    - (1709111130) mejor mensaje de depuración para saber el estado de la aplicación y los datos que gestiona
    - (1709050937C) lista de tránsito visible en todo momento
    - (1709050947C) botón de borrado de pesadas, para vehículos en tránsito (y de nueva pesada)
    - (1707191111) cuando un transporte está pendiente de firmar, no cancelar el formualrio, si no darle a pendiente de firmar. (en vez de pendiente de firmar hemos puesto *retener transporte*)
+ ERRORES:
    - (1709060911) ampliar tamaño de los comboboxes de los productos
    - (1709061239) peso no se reseteaba en la entrada, en los casos de retroceso del formulario
    - (1709061251) desmarcar checkbox de forzar autorización cuando se retrocede del estado 40

#2017/07/25 version 0.0.33 BETHA (primera versión en planta)
+ MEJORAS:
    - camino 2 de entradas ET implementado
    - sistema de incidencias planteado
    - bucle de captura de firma agilizado y log de información aligerado eliminando mensajes de depuración
+ ERRORES:
    - (1707071128) ruta de salvado del pdf de informe
    - (1707071127) revisar la ruta de salvado de los documentos
    - (1707251135) la imagen de firma no se veía correctamente en el pdf del informe.
#2017/07/17 version 0.0.32 ALPHA
+ MEJORAS:
    - (1707121014) incluir logos de biorreciclaje, en bienvenida y entrada ET((1706301154) inserción de logotipos)
    - (1707131147) clase formulario mejorado para ser recuperado cuando cambiamos de pantalla
    - (1707141213) recuperación de formulario cuando venimos de otra pantalla implementado completamente
    - (1706301153) mejorar la estética de los botones de navegación y la estructura de pantalla ((1703271018) plantear estética definitiva ) ( (1706301155) título pantallas más bonito, más centrado, algo de color?)
    - (1706301201) tabla de tránsito en ENtradas ET con información congruente, y seleccionable, modificable el color del seleccionado, etc. (ver posibilidades)
+ ERRORES:
    - (1707141212) arreglo de varios fallos en la estética de botones y frames según qué estados
    - (1706301158) en entradas ET, cambiar *autoriza?* por *autorizar*
#2017/07/07 version 0.0.31 ALPHA
+ MEJORAS:
    - Finalizar descarga en entradas ET implementada (sólo camino *normal* sin incidencias)
    - tabla tránsito creada en base de datos.
    - tabla movimientos creada en base de datos
    - (1707050959) controles de proceso comunes en su propio frame, proceder, cancelar y retroceder.
    - (1706301156) línea intermedia de separación entre entrada a descargar y salida de descargar
    - (1706301157) remarcar el frame de trabajo
+ FALLOS:
    - (1707041028) el peso no se resetea en el cajetín de texto cuando cerramos el formulario.


#2017/06/30 version 0.0.3 ALPHA
+ entradas ET casi terminada, configuración casi terminada, nos acercamos a una versión de pruebas en campo.
+ MEJORAS:
    - (1703271020)construcción de cámara por .ini
    - construcción básculas por .ini
    - tableta de firmas implementada (a falta de mejorar)
    - uso de base de datos sqlite local
    - (1703271017) mostrar versión del programa
    - (1706301158) quitar barra de navegación y trabajar en pantalla completa
    - (1706301218) incluir en el proyecto la configuración del cliente pvbrowser, y los scripts encesarios para la ejecución del programa, etc.
    - (1706301152) resolución pantalla no se ajusta al monitor
#2017/04/26 version 0.0.2 ALPHA
+ FORMULARIO DE PRUEBA
+ NUEVA BASE DE DATOS DEFINITIVA? 6/4/2017
#2017/03/24 version 0.0.1 ALPHA
+ ERROR ARREGLADO(1): volvemos a pantalla de bienvenida y da error de base de datos
+ ERROR ARREGLADO(3): en combobox de clientes puede aparecer 2 veces "ELIJA UNA"
+ ERROR ARREGLADO(4): combobox de LERs no se puebla correctamente
+ ERROR ARREGLADO(5)si volvemos a elegir "ELIJA" en clientes no nos borra los LERs
+ ERROR ARREGLADO(1703231336) si cambiamos de cliente no nos actualiza los LERs
+ MEJORA(6)cambiar ELIJA UNO por ELIJA
+ MEJORA(1703231336)plantear la habilitación y deshabilitación de controles según el estado
