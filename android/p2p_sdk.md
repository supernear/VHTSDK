# p2p

**1 Initialize connection address**

```java
public boolean appGetBSAddress(String userName, String psw) {
       ConfigManager.getInstance().clear();
        AppGetBSAddressRequest request = new AppGetBSAddressRequest(userName, psw, new int[]{3, 4});
        this.submit(new PlatformApiTask(0, request, 10000, 10, 0));
        return true;
    }
```

| Field    | Type   | Describe                           |
| -------- | ------ | ---------------------------------- |
| userName | String | uuid -- Util.getPhoneUUID(context) |
| psw      | String | ""                                 |

**2 get the Device ID**

**3  P2P connection to corresponding server**

````java
GosConnection.TransportProtype();
````

**4 Create a connection channel based on the device ID**

````java
connection =  new UlifeConnection(deviceId, "", "",
                    ConnType.TYPE_P2P, true);

````

| Field        | Type    | Describe                                                  |
| ------------ | ------- | --------------------------------------------------------- |
| devId        | String  | device ID                                                 |
| userName     | String  | login user name, none is ""                               |
| pswWord      | String  | ""                                                        |
| connType     | enum    | 0-UNKNOW,1-TYPE_TUTK,2-TYPE_P2P,3-TYPE_TCP,4-TYPE_P2P_TCP |
| isPushEnable | boolean | Push switch                                               |

**5 connect**

```java
mConnection.connect(0);  //0-default
```

**6 open stream**

````java
int timestamp = (int) (System.currentTimeMillis() / 1000L);
int timezone = (TimeZone.getDefault().getRawOffset() / 3600000) + 24;// on the IPC side, -24,
if(TimeZone.getDefault().inDaylightTime(new Date())){
	 timezone++;
  }
mConnection.startVideo(0, StreamType.VIDEO_AUDIO, "", timestamp, timezone, this);
````

| Field      | Type       | Describe                                                     |
| ---------- | ---------- | ------------------------------------------------------------ |
| channel    | int        | 0- Stream channel number                                     |
| streamType | int        | 0-VIDEO,1-AUDIO,2-VIDEO_AUDIO,3-STREAM_REC,4-STREAM_REC_JPEG |
| psw        | String     | password of Stream ,                                         |
| timestamp  | int        | Current timestamp (seconds)                                  |
| timezone   | int        | TimeZone                                                     |
| IVideoPlay | IVideoPlay | Audio and video stream callback                              |

**7 start talk**

```java
 mConnection.startTalk(0,"");
```

| Field   | Type   | Describe                |
| ------- | ------ | ----------------------- |
| channel | int    | 0 -Sream channel number |
| psw     | String | password of Stream      |

```java
mConnection.stopTalk(0);
```

| Field   | Type | Describe                  |
| ------- | ---- | ------------------------- |
| channel | int  | 0 - Stream channel number |

**8 Resolution modification**

```java
//HD
 mConnection.setStreamQuality(0, VideoQuality.STREAM_HD);
//SD
 mConnection.setStreamQuality(0, VideoQuality.STREAM_SD);
```

| Field         | Type | Describe                |
| ------------- | ---- | ----------------------- |
| channel       | int  | 0-Stream channel number |
| streamQuailty | int  | 0-STREAM_HD,1-STREAM_SD |

**9 Tf playback**

```java
mConnection.startVideo(0, StreamType.STREAM_REC, "", timestamp, timezone, iVideoPlay);  // as same as open stream
mConnection.setLocalStoreCfg(0, mStartTime, 1, 0, "");
```

| Field    | Type   | Describe                                                     |
| -------- | ------ | ------------------------------------------------------------ |
| channel  | int    | 0-Stream channel number                                      |
| utctime  | int    | The start timestamp of a playback video                      |
| type     | int    | 1                                                            |
| duration | int    | The end time of the video, where 0- represents the actual end time of the current video |
| subDevId | String | "",ID of the sub device                                      |

