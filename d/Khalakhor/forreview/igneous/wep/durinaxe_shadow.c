inherit "/std/shadow";

#define ME_DOMAINS ({"Gondor","Shire","Rhovanion"})

//  Prototypes
void notify_left_middle_earth();

int Alarm_id = 0;
object gAxe;

void
set_durinaxe(object axe) 
{
    gAxe = axe;
}

object
query_durinaxe()
{
    return gAxe;
}

int
query_durinaxe_shadow()
{
    return 1;
}

void
remove_durinaxe_shadow()
{
    remove_shadow();
}

void
enter_env(object dest, object old)
{
    if (member_array(dest->query_domain(), ME_DOMAINS) == -1)
    {
	if (!Alarm_id)
	    Alarm_id = set_alarm(1.3,0.0, &notify_left_middle_earth());
    }
    shadow_who->enter_env(dest,old);
}

void
notify_left_middle_earth()
{
    gAxe->left_middle_earth();
    remove_shadow();
}
