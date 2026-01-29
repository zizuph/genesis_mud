#define KARG_DIR "/d/Earthsea/karg/"


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

