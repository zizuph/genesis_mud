#include "defs.h"

inherit SPELL_FILE;

create_spellobj()
{
    set_form(FORM_DIVINATION, 10);
    set_elem(ELEMENT_LIFE, 10);
    set_spell_name("detect magic");
    set_classes( ([1:6]) );
    set_desc(
	"Detects if objects are magic.");
    set_syntax("[on] <what> | here | in me");
}

int type;
#define IN_INV 1
#define IN_ROOM 2
#define IN_ROOM_OBJS 3

object *
area_of_effect(string str)
{
    mixed targets;

    if(!str)
	return 0;

    targets = parse_inventory(str);
    if (sizeof(targets))
    {
	type = IN_INV;
	return targets;
    }

    targets = parse_environment_items(str);
    if(sizeof(targets))
    {
	type = IN_ROOM_OBJS;
	return targets;
    }

    targets = parse_place_in_room(str);
    if (strlen(targets))
    {
	type = IN_ROOM;
	return ({ ENV(caster) });
    }
    return ({});
}

mixed
cast_mult_detect_magic(object *obs, int res)
{
    mixed *id;
    int lvl = level(TP);
    int i,j,is_magic;
    string gs;
    object *mt = ({});

    for(i=0;i<sizeof(obs);i++)
    {
	is_magic = 0;
	id = obs[i]->query_prop(MAGIC_AM_MAGIC);
	for(j=0;j<sizeof(id) && !is_magic;j+=2)
	    if(lvl*5 > id[j])
		is_magic = 1;
	if(is_magic)
	    mt += ({ obs[i] });
    }
    if(!sizeof(mt))
	write("Nothing of "+COMPOSITE_DEAD(obs)+" seems to be magical.\n");
    else if(sizeof(mt)==1)
	write("Only the "+mt[0]->short()+" flashes up as the spell lasts, so it must be magical.\n");
    else
    {
	write(CAP(COMPOSITE_DEAD(mt))+" flashes up as the spell lasts.\n");
	write("You realize that all of these things must be magical.\n");
    }
    return;
}

/* actlab.rtf.utexas.edu */

mixed
cast_detect_magic(object* ob, int res)
{
    mixed *id;
    object o;
    int i, has_ided=0;
    string d1,d2;
    string str="";
    string what;

    if(type==IN_INV)
	what = "on [yourself]";
    else if(type==IN_ROOM)
	what = "here";
    else if(type==IN_ROOM_OBJS)
	what = "on "+COMPOSITE_DEAD(ob);
    else
	what = "somewhere";


    /* tellem(TP, 0, "(You) cast[s] a {Detect Magic;
	mysterious} spell "+what+".\n", 1);*/
	TP->catch_msg("You cast a Detect Magic spell "+what+".\n");
	tell_room(ENV(TP),QCTNAME(caster)+" casts a mysterious spell "+
		what+".\n");
    if(sizeof(ob)>1)
	return cast_mult_detect_magic(ob, res);
    if(!sizeof(ob))
    {
	write("Nothing seems magical.\n");
	return;
    }

    o = ob[0];
    id = o->query_prop(MAGIC_AM_MAGIC);

    for(i=0;i<sizeof(id);i+=2) {
	if(level(TP)*5 > id[i])
	{
	    if(!has_ided)
		str = "The "+o->short()+" seems magical!\nIt";
	    else
		str += " and";

	    if (member_array(id[i+1],
		({"conjuration", "abjuration", "enchantment",
		  "divination", "transmutation", "magic", "spells"})) >=0)
		str += " has been subject to "+id[i+1];
	    else if (sscanf(" "+id[i+1]+" ", "%sslaying%s", d1, d2)==2)
		str += " is "+id[i+1];
	    else if (sscanf(" "+id[i+1]+" ", "%sresistance%s", d1, d2)==2)
		str += " has got "+id[i+1];
	    else if (str=="artifact")
		str += " is an artifact";
	    else
		str += " seems to be "+id[i+1];
	    has_ided = 1;
	}
    }
    if(has_ided)
	TP->catch_msg(str+".\n");
    else
	TP->catch_msg("The "+o->short()+" seems non-magical.\n");
    return;
}

void
do_instant_effect(object *targets, int res)
{
    string retval;

    retval = cast_detect_magic(targets, res);
    if(stringp(retval))
	write(retval);
}
