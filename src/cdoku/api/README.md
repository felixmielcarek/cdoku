# Example of how to test the server

Server terminal :

```bash
make && ./api.out 6363
```
Client terminal :

```bash
socat STDIO TCP:localhost:6363
```
