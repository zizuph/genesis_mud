#define BS(x) break_string(x,75)
#define TP this_player()
#define TO this_object()
#define NF(x) notify_fail(x)
#define C(x) capitalize(x)
#define POS(x) x->query_possessive()
#define OBJ(x) x->query_objective()
#define PRO(x) x->query_pronoun()
#define QtN(obj,beholder) obj->query_the_name(beholder)
#define QtPN(obj,beholder) obj->query_the_possessive_name(beholder)
#define QTN(obj,beholder) obj->query_The_name(beholder)
#define QTPN(obj,beholder) obj->query_The_possessive_name(beholder)
#define ENV(x) environment(x)
#define TR(who,msg) tell_room(ENV(who),msg)
#define me(text) write(text+"\n")
#define LC(x) lower_case(x)
#define MORE(x, y, z) clone_object("/obj/more")->more(x, y, z)
#define EDIT(func) clone_object("/obj/edit")->edit(func)
#define MAIL(subject,sender,recipient,text) "/secure/mail_reader"->\
create_mail(subject,sender,LC(recipient),LC(recipient),text+"\n")
#define STAT(pl,st) pl->query_stat(st)
#define SKILL(pl,sk) pl->query_skill(sk)
#define NUM_TO_STR(n) "/sys/global/language"->word_number(n)
#define SAY_TO(who,what) command("say to "+who->query_real_name()+\
" "+what)

#define TRICKSTERS "/d/Earthsea/tricksters/"
#define TRICKSTER_STD_ROOM TRICKSTERS+"std_room"
#define SERVERO TRICKSTERS+"obj/server"
#define TRICK_SERVER TRICKSTERS+"obj/server"
#define STICK TRICKSTERS+"obj/stick"
#define KIT TRICKSTERS+"obj/kit"
#define RUMEL TRICKSTERS+"obj/rumel"
#define TRICKSTERS_TAX 9
#define GUILD_STYLE "ranger"
#define GUILD_NAME "Tricksters of Kina"
#define TRICKSTERS_SOUL TRICKSTERS+"obj/trick_soul"
#define TRICKSTERS_SHADOW TRICKSTERS+"obj/trick_shadow"
#define STICK_DESC "_trickster_stick_"
#define KIT_DESC "_trickster_kit_"
#define RUMEL_DESC "_trickster_rumel_"
#define INFESTED_ARM_DESC "It seems to have been tampered with.\n"
#define SS_STRANGLE 137001
#define SS_KILL_POINTS 137002
#define MAX_JAMADAR 2
#define SERVER TRICKSTERS+"obj/server"
#define PREP_TIME 4.0
#define RECOVER_TIME 8.0
#define BOOK TRICKSTERS+"txt/book/"
#define HELP TRICKSTERS+"txt/help/"
#define WAGON TRICKSTERS+"obj/wagon"
#define INSIDE_WAGON TRICKSTERS+"inside_wagon"
#define TUNNEL TRICKSTERS+"tunnel"
#define GONT_TUNNEL TRICKSTERS+"gont_tunnel"
#define TRICK_TUNNEL TRICKSTERS+"trick_tunnel"

#define GM_RUMEL_COLOR "golden"
#define LEADER_RUMEL_COLOR "golden"
#define JAMADAR_RUMEL_COLOR "silver"
#define RUMEL_LEVELS ({ ({"green",1}) , ({"yellow",4}) , ({"blue",7}),\
  ({"purple",12}) , ({"red",16}) , ({"black",20}) })

