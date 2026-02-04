/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* An exit blocker. Mortricia 930528. */
inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP       this_player()
#define TO       this_object()
#define ETO      environment(TO)
#define ETP      environment(TP)
#define NF(xx)   notify_fail(xx)
#define FAT_COST 17
#define MIN_DUR  4
#define MAX_DUR  2000

int activated = 0;
int hide;
string b_exit = "";

public void   set_blocked_exit(string exit);
public string query_blocked_exit();
public void   set_duration(int t);

public void
init()
{
    ::init();
    if (ETO == ETP && strlen(b_exit)) {
        add_action("try_exit", b_exit);
    }
}

public void
create_object()
{
    set_name("rainbow");
    set_adj("mysterious");
    set_long("@@my_long");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(MAGIC_AM_MAGIC, ({50, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,
	({"This rainbow seems to be of a magical nature.\n", 5,
	  "You cannot penetrate it unless you are skillful " +
	  "with the magic elements of life.\n", 45}));
    add_prop(MAGIC_I_RES_IDENTIFY, 35);
    add_prop(MAGIC_I_RES_LIFE, 45);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    activated = 0;
    if (!to || living(to)) return;
    
    if (member_array(b_exit, to->query_exit_cmds()) >= 0) {
        activated = 1;
	hide = to->query_prop(ROOM_I_HIDE);
	if (hide >= 0) {
	    to->add_prop(ROOM_I_HIDE, -1);
	}
    }
}

public string
query_blocked_exit()
{
    return b_exit;
}

public void
set_blocked_exit(string exit)
{
    b_exit = exit;
}

public int
try_exit()
{
    if (!activated) return 0;
    if (TP->query_wiz_level() || MEMBER(TP)) {
        write("The "+short()+" does not hinder you.\n");
        say("The "+short()+" does not hinder "+QTNAME(TP)+".\n");
        return 0;
    }
    if (TP->query_skill(SS_ELEMENT_LIFE) > 45 &&
        TP->query_fatigue() >= FAT_COST) {
        write("With some effort you manage to penetrate the " +
              short() + ".\n");
        say("The "+short()+" does not hinder "+QTNAME(TP)+".\n");
        TP->add_fatigue(-FAT_COST);
        return 0;
    }
    write("You cannot go to the " + b_exit + " because of the " +
          short() + ".\n");
    say(QCTNAME(TP) + " was stopped by the "+short()+".\n");
    return 1;
}

public void
self_destruction()
{
    tell_room(ETO, "The "+short()+" fades away.\n");
    if (activated) {
        if (hide == 0) ETO->remove_prop(ROOM_I_HIDE);
        if (hide >= 1) ETO->change_prop(ROOM_I_HIDE, hide);
    }
    remove_object();
}

public void
set_duration(int t)
{
    if (t < MIN_DUR) t = MIN_DUR;
    if (t > MAX_DUR) t = MAX_DUR;
    set_alarm(itof(t), -1.0, self_destruction);
}

public string
my_long()
{
    string s;

    s = "It's a mysterious force field. " +
       "It looks almost like a rainbow, but much smaller. ";
    if (activated) {
        s += "It seems to stop you from going to the "+b_exit+".";
    } else {
        s += "It seems to be floating in the air.";
    }
    return s + "\n";
}
