

#define MANAGER   "/d/Terel/sorgum/wizline/channel_manager"
#define DATABASE  "/d/Terel/sorgum/wizline/channel_data"
#define TRUSTED   ({"sorgum", "mortricia","mercade", "vladimir", "olorin"})

#define TO this_object()
#define TP this_player()
#define NF(xx) notify_fail(xx)

#define WIZLINE_BUSY_PROP  "_wizline_busy"

/*
 * channel protection modes
 */
#define PROT_OPEN   0
#define PROT_CLOSED 1

/*
 * The channel mapping:
 * ([lower-case name:({name, ({users}), ({ }), prot, string owner})]
 */
#define CHANNEL_NAME    0
#define CHANNEL_USERS   1
#define CHANNEL_HUSERS  2
#define CHANNEL_PROT    3
#define CHANNEL_OWNER   4

