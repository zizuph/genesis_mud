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
#define STAT(pl,st) pl->query_stat(st)
#define SKILL(pl,sk) pl->query_skill(sk)
#define NUM_TO_STR(n) "/sys/global/language"->word_number(n)
#define SAY_TO(who,what) command("say to "+who->query_real_name()+\
" "+what)
#define WIZ_LEVEL(who) (SECURITY)->query_wiz_rank\
  (who->query_real_name())
#define WIZ_NM_LEVEL(who) (SECURITY)->query_wiz_rank(who)
#define PLAYER_EXISTS(name) (SECURITY)->exist_player(name)
#define WIZ_DOMAIN(name) (SECURITY)->query_wiz_dom(name)
#define PV(event,prop) query_prop_value(event,prop)
#define RND(x) x[random(sizeof(x))]
#define AOE(x) SECURITY->query_team_member("aoe",x)

#define SCHEDULER_DIR "/d/Earthsea/scheduler/"
#define EVENT_LOG_DIR SCHEDULER_DIR+"log/"
#define HISTORY_LOG_DIR EVENT_LOG_DIR+"history/"
#define SCHEDULER SCHEDULER_DIR+"scheduler"
#define ENGINE SCHEDULER_DIR+"engine"
#define CENGINE SCHEDULER_DIR+"cengine"
#define FAMEHALL SCHEDULER_DIR+"fame_hall"
#define REWARD_LOG EVENT_LOG_DIR+"reward.log"
#define CEVENT_LOG EVENT_LOG_DIR+"cevent.log"
#define SAFE_SHADOW SCHEDULER_DIR+"safe_shadow"

#define NOT_SET -12345

