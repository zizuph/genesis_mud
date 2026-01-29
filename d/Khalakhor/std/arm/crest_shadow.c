inherit "/std/shadow";

#include "/d/Khalakhor/sys/defs.h"
#include <stdproperties.h>
#include <composite.h>

#define ARMOUR 0
#define LONG_DESC 1
#define CREST_SUBLOC  "_khalakhor_crests"

mapping crest = ([]);

int
query_khalakhor_crest_shadow()
{
    return 1;
}

void
set_up_crest(object arm)
{
    string id = arm->query_crest_id();

    if (crest[id])
    {
	crest[id][ARMOUR] += ({arm});
	return;
    }
    shadow_who->add_subloc(CREST_SUBLOC, this_object());
    crest[id] = ({ ({arm}), arm->query_crest_desc() });
}

void
add_crest(object who, object arm)
{
    if (who->query_khalakhor_crest_shadow())
    {
	who->set_up_crest(arm);
	set_alarm(0.0,0.0,remove_shadow);
	return;
    }
    if (!shadow_me(who))
    {
	set_alarm(0.0,0.0,remove_shadow);
	return;
    }
    set_up_crest(arm);
}

void
remove_crest(object arm)
{
    string id = arm->query_crest_id();

    crest[id][ARMOUR] -= ({arm});
    if (!sizeof(crest[id][ARMOUR]))
	crest = m_delete(crest, id);
    if (!sizeof(m_indices(crest)))
    {
	shadow_who->remove_subloc(CREST_SUBLOC);
	remove_shadow();
    }
}
string
show_subloc(string subloc, object who, object for_who)
{
    int i = -1;
    string str = "", *indices;
    object *armours;

    if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
      subloc != CREST_SUBLOC)
    {
	return shadow_who->show_subloc(subloc, who, for_who);
    }

    indices = m_indices(crest);
    while (++i < sizeof(indices))
    {
	armours = crest[indices[i]][ARMOUR];
	str += (who == for_who ? "Your" : capitalize(HIS_HER(who))) + " " +
	COMPOSITE_WORDS(armours->short()) +" "+ (sizeof(armours) > 1 ? "are" : "is") +
	" covered with a crest depicting "+ crest[indices[i]][LONG_DESC] +".\n";
    }

    return str;
}
