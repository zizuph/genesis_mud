//-*-C++-*-
// file name: ~Avenir/common/dark/worm_part.c
// creator(s):  Boriska, July 1994
// last update: Boriska, Mar 29 1995
// purpose:     Common code for body parts of Avenir worm.
// note:
// bug(s):
// to-do:     

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";     // for aggressive
inherit "/std/act/action";      // for actions and emotes

static int body_part; // our index in worm array kept by master
static object master;    // master worm object
static string arrive, depart;  // arrive and depart messages

void
create_creature() { ::create_creature(); }

int
set_index(int i) { body_part = i; }

int
set_master(object obj) { master = obj; }

void
attacked_by(object obj)
{
    if(objectp(master))
	master->notify_attack(obj);  //tell the master we're under attack
    ::attacked_by (obj);
}

void
do_die(object killer)
{
    // notify the master we're dead
    if (objectp(master) && this_object()->query_hp() <= 0) 
	master->notify_death(body_part, killer);
    ::do_die( killer );
}

void
remove_object()
{
    // notify the master about our removal
    // do not notify when its master who removes us.. he knows that
    // anyways. This is done to prevent uncorrect removal while
    // developing (bomb in room with head and master for example)
    if (objectp(master) && previous_object() != master)
	master->notify_death(body_part);
    ::remove_object();
}

void
aggressive_attack(object ob)
{
    if (objectp(master))
	master->notify_attack(ob);  //tell the master we're under attack
    ::aggressive_attack(ob);
}

void
set_arrive(string s) { arrive = s; }

void
set_depart(string s) { depart = s; }

void
leave_env(object from, object to)
{
    ::leave_env();
    if (!from || !to || !from->this_room() || !to->this_room() || !depart)
	return;
    tell_room (from, ({depart, depart, ""}));
}

void
enter_env(object from, object to)
{
    ::leave_env();
    if (!from || !to || !from->this_room() || !to->this_room())
	return;
    tell_room (from, ({arrive, arrive, ""}));
}
