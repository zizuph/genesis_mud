/*
 * apport.c
 *
 * Used in obj/doggystick.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <macros.h>

object owner, *victims;
string dir;

void ta();
void tillbax(mixed *baba);
void ge(mixed *baba);
string find_where();

void
set_dir(string s)
{
    dir = s;
}

void
set_owner(object o)
{
    owner = o;
}

void
set_victims(object *v)
{
    victims = v;
}

void
create_object()
{
    set_short("apport!");
    set_no_show();
}

void
init()
{
    add_action("say","say");
}

object *
filtrera_bort(object *a)
{
    object *b;
    int i;

    b=({});

    for(i=0;i<sizeof(a);i++)
        if ((owner->query_wiz_level() || 
             member_array("dog", a[i]->query_names())>-1) && 
            !a[i]->query_prop("_roke_i_no_apport"))
            b += ({a[i]});

    return b;
}

void
spring()
{
    victims->catch_msg("You run " + dir + ".\n");
    victims->move_living(dir, find_where());
    set_alarm(1.0, 0.0, ta);
}

void
apportera()
{
    victims = filtrera_bort(victims);
    if (!sizeof(victims))
    {
        owner->catch_msg("Noone really cares. Most likely you'll have to get it yourself.\n");
        remove_object();
        return;
    }

    victims->catch_msg("You feel a sudden urge to run " + dir +
                       ", after the stick.\n");
    set_alarm(1.0, 0.0, spring);
}

int
say(string s)
{
    if (s == "fetch" || s == "fetch!")
        set_alarm(1.0, 0.0, apportera);

    return 0;
}

string
find_where()
{
    string *s;
    string a;

    s = ENV(victims[0])->query_exit();
    a = s[member_array(dir,s)-1];
    return a;
}


void
ta()
{
    int index;
    object stick;

    stick = present("doggystick", environment(victims[index]));
  
    if(stick)
    {
        if(sizeof(victims)>1)
            victims->catch_msg("You struggle a little about the stick.\n");
        index = random(sizeof(victims));
  
        victims[index]->catch_msg("You take the stick.\n");
        tell_room(ENV(victims[index]),
                  QCTNAME(victims[index]) + " takes the stick.\n",
                  ({victims[index]}));
        stick->move(victims[index]);
    }
    else
        victims->catch_msg("You all feel rather stupid when you notice that "+
                           "the stick is gone.\n");
     
    
    set_alarm(1.0, 0.0, &tillbax(({index,stick})));
}

void
tillbax(mixed *baba)
{
    victims->catch_msg("You quickly run back to "+QCTNAME(owner)+".\n");
    victims->move_living("quickly",environment(owner));
  
    set_alarm(1.0, 0.0, &ge(baba));
}

void
ge(mixed *baba)
{
    int index;
    object stick;

    index = baba[0];
    stick = baba[1];

    if(stick)
    {
        victims->catch_msg("You return to "+QCTNAME(owner)+".\n");
        victims[index]->catch_msg("You give the stick to "+QCTNAME(owner)+".\n");
        tell_room(environment(owner),QCTNAME(victims[index])+" gives a stick to "+
                  QCTNAME(owner)+".\n",({victims[index],owner}));
        owner->catch_msg(QCTNAME(victims[index])+" gives you the stick.\n");
        stick->move(owner);
    }
    else
    {
        victims->catch_msg("You apologize for not having the stick.\n");
        owner->catch_msg("Everyone tries to explain where the stick is.\n");
    }

    remove_object();
}
