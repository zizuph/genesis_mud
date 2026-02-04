#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <language.h>
#include <tasks.h>
#include <ss_types.h>

inherit "/std/shadow";

int is_invis, old_sneak, old_hide;

public void clean_me()
{
	remove_shadow();
	shadow_who->remove_adj("red-painted");
	if(is_invis)
		shadow_who->set_invis(1);
	shadow_who->set_skill_extra(SS_SNEAK, 0);
	shadow_who->set_skill_extra(SS_HIDE, 0);
	
}

public void trap_me(object ppl)
{
	shadow_me(ppl);
	object paint_object = clone_object(BHTRAPS + "paint_object");
	paint_object->move(ppl);
	is_invis = ppl->query_invis();
	if(is_invis)
		ppl->set_invis(0);
	
	shadow_who->add_adj("red-painted");
	old_sneak = shadow_who->query_skill(SS_SNEAK);
	old_hide = shadow_who->query_skill(SS_HIDE);
	shadow_who->set_skill_extra(SS_SNEAK, -old_sneak);
	shadow_who->set_skill_extra(SS_HIDE, -old_hide);
}

public void set_invis(int arg)
{
	if(arg)
		is_invis = 1;
	else
		is_invis = 0;
}

mixed query_adj(int arg)
{
	if(arg)
		return ({"red-painted"});
	return "red-painted";
}

string query_nonmet_name()
{
	if(!is_invis)
		return shadow_who->query_nonmet_name();
	return "red-painted shape of " + LANG_ADDART(shadow_who->query_race_name());
}



