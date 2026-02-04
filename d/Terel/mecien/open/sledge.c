/* A sledge room. Mortricia 930606 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 72)
#define BSN(message)    break_string(message + "\n", 72)
#define TP              this_player()
#define TO              this_object()
#define NF(xx)          notify_fail(xx + "\n")
#define MAX_SCORES      10
#define MAX_TRY         3

#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"
#define HIGHEST_SCORES  CAMP_DIR + "highest_scores"

int *scores;
string *names;
object mr_strong, sledge;
object hitter;
int hits;
int half_ran(int n);
void update_scores(int n, object who);
string show_scores();
string pad(string str, int z_length);
void hit_res(int n, object who);
void set_hitter(object ob);
void reset_hits();

void
reset_room()
{
    if (!mr_strong) {
        mr_strong = clone_object(CAMP_DIR + "jolmar");
        sledge = clone_object(CAMP_DIR + "w_club");
        sledge -> move(mr_strong);
        mr_strong -> move(TO);
    }
}

void
init()
{
    ::init();
    add_action("do_hit", "hit");
}

void
create_room()
{
    set_short("At the club device");
    set_long(BSN(
        "You are standing in the westermost part of the camp. South "+
        "from here you see the canvas of a strange tent. " +
	"Here is also a device where you can test your strength."
    ));

    add_item(({"tent", "strange tent"}), BSN(
        "Indeed, it's very strange!"
    ));
    add_item("canvas", "You cannot see through it.\n");
    add_item(({"scores", "score list", "list", "table"}),
             "@@show_scores");
    add_item(({"device"}), BSN(
	"It's a small wooden tower with a bell at the top. " +
	"At the foot of the tower is a small wooden peg, which " +
	"when hit by a club will accelerate a weight along two " +
	"rails. Along the rails is a scale, numbered from zero up " +
	"one hundred. The bell is attached at one hundred."
    ));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(CAMP_DIR + "camp_09", "east" , "@@check");

    scores = allocate(MAX_SCORES);
    names  = allocate(MAX_SCORES);

    hits = 0;
    reset_room();
}

check()
{
    object *ob;

    if (!mr_strong) return 0;
    if (TP == mr_strong) return 0;
    if (environment(mr_strong) != TO) return 0;
    if (environment(sledge) == TP) {
        mr_strong->command("say Oh no! Give back the "+sledge->short()+".");
        mr_strong->command("stare at "+TP->query_real_name());
        return 1;
    }
    return 0;
}

do_hit(string str)
{
    object *ob;
    int i;
    string s1, s2;

    NF("There is no one here to maintain the device.");
    if (!mr_strong) return 0;

    NF("Hit what with what?");
    if (!str) return 0;
    if (sscanf(str, "%s with %s", s1, s2) != 2) return 0;
    if (s1 != "peg" && s1 != "wooden peg") return 0;
    ob = FIND_STR_IN_OBJECT(s2, TP);
    if (sizeof(ob) == 0) return 0;
    if (ob[0]->short() != sledge->short()) {
	mr_strong->command("say You cannot use the " +
	                   ob[0]->short()+" here.");
	return 1;
    }
    if (TP != hitter) {
        mr_strong->command("say You must pay first.");
        return 1;
    }
    if (hits >= MAX_TRY) {
	reset_hits();
        mr_strong->command("say You must pay again.");
        return 1;
    }

    hits++;
    write("You hit the peg with the "+ob[0]->short()+".\n");
    say(QCTNAME(TP)+" hits the peg with the "+ob[0]->short()+".\n");

    i = half_ran(TP->query_stat(SS_STR));
    i += half_ran(TP->query_stat(SS_DEX));
    i += half_ran(TP->query_skill(SS_WEP_CLUB));
    i /= 3;

    if (i > 100) i = 100;
    hit_res(i, TP);
    if (TP != mr_strong) update_scores(i, TP);
    return 1;
}

int
half_ran(int n)
{
    return (n + random(n))/2;
}

void
hit_res(int n, object who)
{
    string s;

    if (n == 100) {
        tell_room(TO, "PLING-PLING\n");
        if (who == mr_strong) {
            mr_strong->command("smile");
        } else {
            mr_strong->command("gasp");
        }
    } else {
        s = "say You got ";
        if (who == mr_strong) s = "say I got ";
        mr_strong->command(s + LANG_WNUM(n)+"!");
    }
    return;
}

void
update_scores(int n, object who)
{
    int i, j;

    for (i=0; i<MAX_SCORES; i++) {
        if (n >= scores[i]) {
            for (j=MAX_SCORES-1; j>i; j--) {
                scores[j] = scores[j-1];
                names[j] = names[j-1];
            }
            scores[i] = n;
            names[i] = who->query_name();
            mr_strong->command("say That was a good one.");
            tell_room(TO, QCTNAME(mr_strong) +
                    " writes the result on the score list.\n");
            return;
        }
    }
}

string
show_scores()
{
    int i;
    string s="";

    for (i=0; i<MAX_SCORES; i++) {
        if (strlen(names[i])) {
            s += pad(names[i], 21) + pad(LANG_WNUM(scores[i]), 21) + "\n";
        }
    }
    if (strlen(s) == 0) s = "It's empty.\n";
    return s;
}

string
pad(string str, int z_length)
{
    string space;

    space = "                                                 ";
    return str + extract(space, 0, z_length - strlen(str));
}

void
set_hitter(object ob)
{
    hits = 0;
    hitter = ob;
}

void
reset_hits()
{
    hits = 0;
    hitter = 0;
}
