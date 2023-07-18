## complie && run

isntall iconv

```
wget http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.13.1.tar.gz 
tar zxvf libiconv-1.13.1.tar.gz && cd libiconv-1.13.1 
./configure --prefix=/usr/local 
make 
make install 

ln -s /usr/local/lib/libiconv.so /usr/lib 
ln -s /usr/local/lib/libiconv.so.2 /usr/lib/libiconv.so.2 
```

install uuid

```
sudo apt-get install uuid
```


compile sample

```
chmod +x build.sh
./build.sh linux
make
```

run sample

```
./sample
```

stop sample

```
input  "q"
```



## function & base running

```C
Turn_SetLogLevel(4)

Turn_Devability_Set(0, &turn_capbility);
Turn_Params_Set("A99ZC210NLC8ZTX", "cnp2p.ulifecam.com:6001", &turn_params);
Turn_Cb_Set(&turn_cb);
Turn_Initialize(E_Turn_Mode_P2P, 500*1024, 10, turn_capbility.p2p_port_guess);
Turn_InitDeviceCapability(&turn_capbility, &turn_params, &turn_cb);

Turn_StartService();
```



## set device id & p2p dispatch address

```C
// A99ZC210NLC8ZTX has been authorized on service cnp2p.ulifecam.com:6001
Turn_Params_Set("A99ZC210NLC8ZTX", "cnp2p.ulifecam.com:6001", &turn_params);
```



## register setting & state callback funciton

```C
Turn_Cb_Set(&turn_cb);

int Turn_Cb_Set(Turn_cb* turn_cb)
{
	memset(turn_cb, 0, sizeof(Turn_cb));
	turn_cb->on_turn_recv_speak_data = Turn_On_SpeakData;
	turn_cb->on_turn_service_state = Turn_On_ServerState;
	turn_cb->on_turn_recv_user_cmd = Turn_On_UserCmd;
	
	return 0;
}
```



## start & strop live stream

```
int Turn_On_LiveStart(TurnConn conn, int type, void* data, int length);

int Turn_On_LiveStop(TurnConn conn, int type, void* data, int length);
```



## modify video quality

```
int Turn_On_VideoQuality_Set(TurnConn conn, int type, void* data, int length);
```



## record file replay

```
int Turn_On_Replay_Start(TurnConn conn, int type, void* data, int length);
```



## talk intercom

```
// data: frame_head + g711a pure data    length: sizeof(frame_head) + pure data size
int Turn_On_SpeakData(TurnConn conn, int type, void* data, int length)
```

