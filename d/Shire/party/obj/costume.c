inherit "/std/shadow";

#include <macros.h>
#include <config.h>

string Race_name = "frog";
string Race_say = "croaks";
string Adj1 = "ugly", Adj2 = "warty";
string In = "arrives hopping", Out = "leaps";

void
set_up_costume(string *var)
{
    Race_name = var[0];
    Adj1     =  var[1];
    Adj2     =  var[2];
    Race_say =  var[3];
    In       =  var[4];
    Out      =  var[5];
}

int
query_shire_costume()
{
    return 1;
}

void
remove_shire_costume()
{
    remove_shadow();
}

public string
race_sound()
{
    return Race_say;
}

varargs public mixed
query_adj()
{
    return ({Adj1,Adj2});
}

string
query_m_in()
{
    return In;
}

string
query_m_out()
{
    return Out;
}

string
query_race_name()
{
    return Race_name;
}

string
query_nonmet_name() 
{
    return Adj1+" "+Adj2+" "+shadow_who->query_gender_string()+
    " "+Race_name; 
}

string *
parse_command_adjectiv_id_list()
{
    return ({Adj1, Adj2});
}

string *
parse_command_id_list()
{
    return shadow_who->parse_command_id_list() + ({Race_name});
}

void
enter_env(object env, object from)
{
    shadow_who->enter_env(env,from);

    if (env->query_shire_party_room())
	return;
    if (file_name(env) == OWN_STATUE)
	return;

    remove_shire_costume();
}
