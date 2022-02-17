# SDSP
Simple Drone Serial Protocol

As the name describes, SDSP was created to be simple and straight forward. It also can incorporate additional data chunks, or “chunk” for short, which can be individually defined by the designer of the chunk. This protocol is broken into 2 parts, header and payload, which will be represented below.

<pre>
|------------------------------------------------------------------|
|        Header                  |              Payload            |
|--------------------------------|---------------------------------|
|  4 bytes   |       4 bytes     | < Length of message > - 8 bytes |
| Validation | Length of message |               Chunks            |
|------------------------------------------------------------------|
</pre>

Chunks will be broken down into chunks. Each chunk will be represted as the following.
<pre>
|------------------------------------------------------------------|
|                              Chunk                               |
|--------------------------------|---------------------------------|
|    4 bytes    |       4 bytes     | < Size of chunk > - 8 bytes  |
| Size of chunk |        Type       |           Chunk data         |
|------------------------------------------------------------------|
</pre>

The header **Validation** will consist of a 4 byte sequence with the following order **0XA5'5A'69'01**. Any message not containing this header will get droped. 

Chunk types should be case sensitive and should be represtened as chars following ASCii format. The following are defined types that being used in operations.
| TYPE | Meaning            |            use               |
|------|--------------------|------------------------------|
| TOLM | Top Left Motor     | First 2 bytes are hz for ESC |
| TORM | Top Right Motor    | First 2 bytes are hz for ESC |
| BOLM | Bottom Left Motor  | First 2 bytes are hz for ESC |
| BORM | Bottom Right Moto  | First 2 bytes are hz for ESC |

As mentioned before, chunks can be added into the protocol. This keeps the protocol small, simple, yet allows for future development. Also notice that there is no bit error correction, check sum, or redundancy check. This addition adds quit a hefty overhead, which this current project is trying to avoid. It also adds complications which out of the scope of this project. 
