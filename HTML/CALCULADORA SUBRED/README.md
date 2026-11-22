# Calculadora de Subredes IPv4

Calculadora web para obtener información de una subred IPv4 a partir de una dirección IP y una máscara de subred.

## Descripción

El proyecto permite ingresar una dirección IPv4 junto con una máscara mediante prefijo CIDR, número de prefijo o máscara decimal. Después calcula la dirección de red, la máscara wildcard, el rango de hosts utilizables y la dirección de broadcast.

También muestra una representación binaria de la dirección IP, la máscara, la red y el broadcast, usando colores para identificar los bits de red y de host.

## Características

- Cálculo de dirección de red y broadcast.
- Soporte para prefijos `/0` a `/32`.
- Acepta prefijos como `/26`, `26` o máscaras como `255.255.255.192`.
- Muestra el primer y último host utilizables.
- Indica el total de direcciones y los hosts utilizables.
- Detecta máscaras no contiguas y direcciones IPv4 inválidas.
- Identifica clases de dirección y rangos privados RFC 1918.
- Incluye soporte especial para redes `/31` y `/32`.
- Presenta información binaria con resaltado de colores.
- Interfaz adaptable para escritorio y dispositivos móviles.
- Incluye modos de tema claro y oscuro según la configuración del sistema.

## Formatos admitidos

### Dirección IP

Ejemplo:

```text
192.168.10.45
```

### Máscaras

Ejemplo de prefijo CIDR:

```text
/26
```

Ejemplo de número de prefijo:

```text
26
```

Ejemplo de máscara decimal:

```text
255.255.255.192
```

## Uso

1. Abra `CALCULADORA_SUBRED.HTML` en cualquier navegador web moderno.
2. Introduzca una dirección IPv4.
3. Introduzca la máscara de subred en uno de los formatos admitidos.
4. Presione **Calcular**.
5. Consulte los resultados en la sección de información y en la vista binaria.

El botón **Usar ejemplo** carga `192.168.10.45/26`. El botón **Limpiar** vacía los campos y los resultados.

## Ejemplo

Para:

```text
IP: 192.168.10.45
Máscara: /26
```

La calculadora devuelve información correspondiente a la subred:

```text
Red: 192.168.10.0/26
Máscara: 255.255.255.192
Broadcast: 192.168.10.63
Primer host: 192.168.10.1
Último host: 192.168.10.62
Hosts utilizables: 62
Total de direcciones: 64
```

## Casos especiales

- **`/31`:** se considera un enlace punto a punto según RFC 3021; ambas direcciones son utilizables.
- **`/32`:** representa un único host.
- **`/30` y menores:** se excluyen la dirección de red y de broadcast del rango utilizable.
- Las máscaras IPv4 deben contener unos seguidos por ceros.

## Archivos

```text
CALCULADORA SUBRED/
├── CALCULADORA_SUBRED.HTML
└── README.md
```

## Tecnologías

- HTML5
- CSS3
- JavaScript

No requiere instalación, dependencias ni conexión a Internet para ejecutarse.
