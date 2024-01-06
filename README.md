# C Chat Server
This is POC socket example. 

## Setup Code
### Install Source Code 
Clone tih project with GIT
```bash
git clone c-server
```
Go into directory

```bash
cd c-server
``` 

### Run Code

**Defines**:
You can change those variables what you want. Add `-D<variable-name>=<value>` to `FLAGS` variables at `makefile`
> Example: `-DPORT=8080`

`PORT`: Server listen this port. Default value is `3000`

`MAX_CONN`: Maximmum connection count. Default value is `10`

**Compile and Run:**
`make` command compile `src/server.c` file to `bin` folder then run `bin/server` executable.

# License
This project is under the [MIT](./LICENSE) license.
