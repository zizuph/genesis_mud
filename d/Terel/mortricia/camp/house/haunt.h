#define NO_OF_HAUNTS 3

void haunt(object who);

void
haunt(object who)
{
    int i, is_enemy=0;
    string name, race;
    object *enemies;

    if (who->query_race_name() == this_object()->query_race_name())
        return;
    enemies = who->query_enemy(-1);
    if (member_array(this_object(), enemies) >= 0) is_enemy = 1;

    i = random(NO_OF_HAUNTS);
    this_object()->command("scream");
    if (environment(who) == environment(this_object()) && is_enemy) {
        name = lower_case(who -> query_name());
        race = capitalize(who -> query_race_name());
	if (i==0) {
            this_object()->command("stare at "+name);
            this_object()->command("whisper "+name+" "+race+"!"+
                      " I'll remember you!"); 
	    this_object()->set_follow(who->query_real_name());
	}
	if (i==1) {
            this_object()->command("spit "+name);
            this_object()->command("whisper "+name+" "+race+"!"+
                      " I hate your kind!"); 
	}
	if (i==2) {
            this_object()->command("tackle "+name);
            this_object()->command("whisper "+name+" "+race+"!"+
                      " I wish you were dead."); 
	}
    }
}
