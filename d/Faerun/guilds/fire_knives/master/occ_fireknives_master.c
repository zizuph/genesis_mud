/*
 * Guild manager, master
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

#include <files.h>
#include <std.h>
#include <stdproperties.h>
#include "../guild.h";


void create();

// Librarians list
private string *occ_fireknives_librarian_list = ({ });

// Whisper list
private string *occ_fireknives_whisper_list = ({ });

// Retired council honourable list
private string *occ_retired_council_list = ({ });

// Fire Knives list
private string *occ_fireknives_list = ({ });

// Fire Knives leadership list (mentor)
private string *occ_fireknives_mentor_list = ({ });

// Fire Knives leadership list (the fist)
private string *occ_fireknives_thefist_list = ({ });

// Fire Knives boss list (the elder)
private string *occ_fireknives_boss_list = ({ });

// Guild fullmember list
private string *guild_fullmember_list = ({ });

// Guild trainee list
private string *guild_trainee_list = ({ });

// Guild enemy list
private string *guild_enemy_list = ({ });

// Guildclub memberlist
private string *crow_list = ({ });


int boss_activity;
int mentor_activity;
int fist_activity;


int
is_occ_whisper(string name)
{
    name = capitalize(name);

    if (member_array(name, occ_fireknives_whisper_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_occ_whisper(string name)
{  
    name = capitalize(name);

    if (is_occ_whisper(name) == 1)
    {
        return;
    }

    occ_fireknives_whisper_list += ({ name });

    sort_array(occ_fireknives_whisper_list);
    
    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_occ_whisper(string name)
{
    name = capitalize(name);

    if (is_occ_whisper(name) != 1)
    {
        return;
    }

    occ_fireknives_whisper_list -= ({ name });
    
    sort_array(occ_fireknives_whisper_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


int
is_occ_retired_council(string name)
{
    name = capitalize(name);

    if (member_array(name, occ_retired_council_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_occ_retired_council(string name)
{  
    name = capitalize(name);

    if (is_occ_retired_council(name) == 1)
    {
        return;
    }

    occ_retired_council_list += ({ name });

    sort_array(occ_retired_council_list);
    
    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_occ_retired_council(string name)
{
    name = capitalize(name);

    if (is_occ_retired_council(name) != 1)
    {
        return;
    }

    occ_retired_council_list -= ({ name });
    
    sort_array(occ_retired_council_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


int
is_occ_librarian(string name)
{
    name = capitalize(name);

    if (member_array(name, occ_fireknives_librarian_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_occ_librarian(string name)
{  
    name = capitalize(name);

    if (is_occ_librarian(name) == 1)
    {
        return;
    }

    occ_fireknives_librarian_list += ({ name });

    sort_array(occ_fireknives_librarian_list);
    
    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_occ_librarian(string name)
{
    name = capitalize(name);

    if (is_occ_librarian(name) != 1)
    {
        return;
    }

    occ_fireknives_librarian_list -= ({ name });
    
    sort_array(occ_fireknives_librarian_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


int
is_occ_fireknife(string name)
{
    name = capitalize(name);

    if (member_array(name, occ_fireknives_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_occ_fireknife(string name)
{  
    name = capitalize(name);

    if (is_occ_fireknife(name) == 1)
    {
        return;
    }

    occ_fireknives_list += ({ name });

    sort_array(occ_fireknives_list);
    
    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_occ_fireknife(string name)
{
    name = capitalize(name);

    if (is_occ_fireknife(name) != 1)
    {
        return;
    }

    occ_fireknives_list -= ({ name });
    
    sort_array(occ_fireknives_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


int
is_crow(string name)
{
    name = capitalize(name);

    if (member_array(name, crow_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_crow(string name)
{  
    name = capitalize(name);

    if (is_crow(name) == 1)
    {
        return;
    }
    
    if (is_occ_fireknife(name) == 1)
    {
        return;
    }

    crow_list += ({ name });

    sort_array(crow_list);
    
    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_crow(string name)
{
    name = capitalize(name);

    if (is_crow(name) != 1)
    {
        return;
    }

    crow_list -= ({ name });
    
    sort_array(crow_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


int
is_occ_mentor_fireknife(string name)
{
    name = capitalize(name);

    if (member_array(name, occ_fireknives_mentor_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_occ_mentor_fireknife(string name)
{  
    name = capitalize(name);

    if (is_occ_mentor_fireknife(name) == 1)
    {
        return;
    }

    occ_fireknives_mentor_list += ({ name });

    sort_array(occ_fireknives_mentor_list);
    
    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_occ_mentor_fireknife(string name)
{
    name = capitalize(name);

    if (is_occ_mentor_fireknife(name) != 1)
    {
        return;
    }

    occ_fireknives_mentor_list -= ({ name });
    
    sort_array(occ_fireknives_mentor_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


int
is_occ_thefist_fireknife(string name)
{
    name = capitalize(name);

    if (member_array(name, occ_fireknives_thefist_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_occ_thefist_fireknife(string name)
{  
    name = capitalize(name);

    if (is_occ_thefist_fireknife(name) == 1)
    {
        return;
    }

    occ_fireknives_thefist_list += ({ name });

    sort_array(occ_fireknives_thefist_list);
    
    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_occ_thefist_fireknife(string name)
{
    name = capitalize(name);

    if (is_occ_thefist_fireknife(name) != 1)
    {
        return;
    }

    occ_fireknives_thefist_list -= ({ name });
    
    sort_array(occ_fireknives_thefist_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


int
is_occ_boss_fireknife(string name)
{
    name = capitalize(name);

    if (member_array(name, occ_fireknives_boss_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_occ_boss_fireknife(string name)
{  
    name = capitalize(name);

    if (is_occ_boss_fireknife(name) == 1)
    {
        return;
    }

    occ_fireknives_boss_list += ({ name });

    sort_array(occ_fireknives_boss_list);
    
    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_occ_boss_fireknife(string name)
{
    name = capitalize(name);

    if (is_occ_boss_fireknife(name) != 1)
    {
        return;
    }

    occ_fireknives_boss_list -= ({ name });
    
    sort_array(occ_fireknives_boss_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


int
is_guild_enemy(string name)
{
    name = capitalize(name);

    if (member_array(name, guild_enemy_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_guild_enemy(string name)
{
    name = capitalize(name);
    
    if (is_guild_enemy(name) == 1)
    {
        return;
    }

    guild_enemy_list += ({ name });
    
    sort_array(guild_enemy_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_guild_enemy(string name)
{
    name = capitalize(name);
    
    if (is_guild_enemy(name) != 1)
    {
        return;
    }

    guild_enemy_list -= ({ name });
    
    sort_array(guild_enemy_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}



//////////////////////////////////////////

int
is_guild_trainee(string name)
{
    name = capitalize(name);

    if (member_array(name, guild_trainee_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_guild_trainee(string name)
{
    name = capitalize(name);
    
    if (is_guild_trainee(name) == 1)
    {
        return;
    }

    guild_trainee_list += ({ name });
    
    sort_array(guild_trainee_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_guild_trainee(string name)
{
    name = capitalize(name);
    
    if (is_guild_trainee(name) != 1)
    {
        return;
    }

    guild_trainee_list -= ({ name });
    
    sort_array(guild_trainee_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


/////////////////////////////////////////////

int
is_guild_fullmember(string name)
{
    name = capitalize(name);

    if (member_array(name, guild_fullmember_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_guild_fullmember(string name)
{
    name = capitalize(name);
    
    if (is_guild_fullmember(name) == 1)
    {
        return;
    }

    guild_fullmember_list += ({ name });
    
    sort_array(guild_fullmember_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


void
remove_guild_fullmember(string name)
{
    name = capitalize(name);
    
    if (is_guild_fullmember(name) != 1)
    {
        return;
    }

    guild_fullmember_list -= ({ name });
    
    sort_array(guild_fullmember_list);

    save_object(FIREKNIVES_SAVE_FILE);

    return;
}


string
list_boss()
{
    string boss;

	occ_fireknives_boss_list = sort_array(occ_fireknives_boss_list);

    for (int i = 0; i < sizeof(occ_fireknives_boss_list); i++) 
    {
        if (i == 0)
        {
            boss = occ_fireknives_boss_list[i];
        }
        
        if (i > 0)
        {
            boss = occ_fireknives_boss_list[i];
        }
    }

    return boss;
}


string
list_mentor()
{
    string mentor;

	occ_fireknives_mentor_list  = sort_array(occ_fireknives_mentor_list);

    for (int i = 0; i < sizeof(occ_fireknives_mentor_list); i++) 
    {
        if (i == 0)
        {
            mentor = occ_fireknives_mentor_list[i];
        }
        
        if (i > 0)
        {
            mentor = occ_fireknives_mentor_list[i];
        }
    }

    return mentor;
}


string
list_fist()
{
    string fist;

	occ_fireknives_thefist_list  = sort_array(occ_fireknives_thefist_list);

    for (int i = 0; i < sizeof(occ_fireknives_thefist_list); i++) 
    {
        if (i == 0)
        {
            fist = occ_fireknives_thefist_list[i];
        }
        
        if (i > 0)
        {
            fist = occ_fireknives_thefist_list[i];
        }
    }

    return fist;
}


string
list_guild_members()
{
    string list;

	occ_fireknives_boss_list = sort_array(occ_fireknives_boss_list);
	occ_fireknives_mentor_list  = sort_array(occ_fireknives_mentor_list);
	occ_fireknives_thefist_list  = sort_array(occ_fireknives_thefist_list);
	
	guild_fullmember_list = sort_array(guild_fullmember_list);
	guild_trainee_list = sort_array(guild_trainee_list);

	
    for (int i = 0; i < sizeof(occ_fireknives_boss_list); i++) 
    {
        if (i == 0)
        {
			
			
            list = "The Elder: " + occ_fireknives_boss_list[i] + "\n";
        }
        
        if (i > 0)
        {
            list = list + "The Elder: " + occ_fireknives_boss_list[i] + "\n";
        }
    }
	
	
	for (int i = 0; i < sizeof(occ_fireknives_mentor_list); i++) 
    {
        if (i == 0)
        {
            list = list + "The Inquisitor: " + occ_fireknives_mentor_list[i] + "\n";
        }
        
        if (i > 0)
        {
            list = list + "The Inquisitor: " + occ_fireknives_mentor_list[i] + "\n";
        }
    }
	
	
	for (int i = 0; i < sizeof(occ_fireknives_thefist_list); i++) 
    {
        if (i == 0)
        {
            list = list + "The Fist: " + occ_fireknives_thefist_list[i] + "\n";
        }
        
        if (i > 0)
        {
            list = list + "The Fist: " + occ_fireknives_thefist_list[i] + "\n";
        }
    }
	
		
	for (int i = 0; i < sizeof(guild_fullmember_list); i++) 
    {
        if (i == 0)
        {
            list = list + "Member: " + guild_fullmember_list[i] + "\n";
        }
        
        if (i > 0)
        {
            list = list + "Member: " + guild_fullmember_list[i] + "\n";
        }
    }
	
	
	for (int i = 0; i < sizeof(guild_trainee_list); i++) 
    {
        if (i == 0)
        {
            list = list + "Trainee: " + guild_trainee_list[i] + "\n";
        }
        
        if (i > 0)
        {
            list = list + "Trainee: " + guild_trainee_list[i] + "\n";
        }
    }
    
    return list;
}


string
list_guild_enemies()
{
    string list;
    
    guild_enemy_list = sort_array(guild_enemy_list);
    
    for (int i = 0; i < sizeof(guild_enemy_list); i++) 
    {
        if (i == 0)
        {
            list = "- " + guild_enemy_list[i] + "\n";
        }
        
        if (i > 0)
        {
            list = list + "- " + guild_enemy_list[i] + "\n";
        }
    }
    
    return list;
}


string
list_crows_list()
{
    string list;
    
    crow_list = sort_array(crow_list);
    
    for (int i = 0; i < sizeof(crow_list); i++) 
    {
        if (i == 0)
        {
            list = "- " + crow_list[i] + "\n";
        }
        
        if (i > 0)
        {
            list = list + "- " + crow_list[i] + "\n";
        }
    }
    
    return list;
}


int
query_activity_meter_boss()
{
    return boss_activity;
}


int
query_activity_meter_mentor()
{
    return mentor_activity;
}


int
query_activity_meter_fist()
{
    return fist_activity;
}


int
add_activity_point_boss()
{
    string boss;
	string mentor;
	string fist;
		
	boss = list_boss();
	mentor = list_mentor();
	fist = list_fist();
	
	boss_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(boss);
	mentor_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(mentor);
	fist_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(fist);   
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()))
	{
        int fist_activity;
        fist_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(this_player()->query_name());
        
	    fist_activity = fist_activity +1;
	    FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(this_player()->query_name(), fist_activity);
    }
}


// Activitymeter
void
activity_meter()
{
	string boss;
	string mentor;
	string fist;
		
	boss = list_boss();
	mentor = list_mentor();
	fist = list_fist();
	
	boss_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(boss);
	mentor_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(mentor);
	fist_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(fist);
		
	if (boss_activity > 0)
    {
		if (is_occ_boss_fireknife(boss) == 1)
		{
	        boss_activity = boss_activity -1;
            
            if (boss_activity < 1)
            {
                boss_activity = 1;
            }
            
	        FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(boss, boss_activity);
		}
	}
	
	if (mentor_activity > 0)
    {
        if (is_occ_mentor_fireknife(mentor) == 1)
		{
            mentor_activity = mentor_activity -1;
            
            if (mentor_activity < 1)
            {
                mentor_activity = 1;
            }
            
            FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(mentor, mentor_activity);
        }
	}
	
	if (fist_activity > 0)
    {
        if (is_occ_thefist_fireknife(fist) == 1)
		{
            if (fist_activity < 1)
            {
                fist_activity = 1;
            }
            
            fist_activity = fist_activity -1;
            FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(fist, fist_activity);
        }
	}
	
	if (is_occ_boss_fireknife(boss) == 1)
	{
		if (boss_activity < 5)
		{
			remove_occ_boss_fireknife(boss);
		    add_guild_fullmember(boss);
		    FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(boss);
            FIREKNIVES_MAPPINGS->set_assassin_xcouncil_activity_cooldown(boss, 1);            
		}
	}
    
    if (is_occ_mentor_fireknife(mentor) == 1)
	{
		if (mentor_activity < 5)
		{
			remove_occ_mentor_fireknife(mentor);
		    add_guild_fullmember(mentor);
		    FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(mentor);
            FIREKNIVES_MAPPINGS->set_assassin_xcouncil_activity_cooldown(mentor, 1);            
		}
	}
    
    if (is_occ_thefist_fireknife(fist) == 1)
	{
		if (fist_activity < 5)
		{
			remove_occ_thefist_fireknife(fist);
		    add_guild_fullmember(fist);
		    FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(fist); 
            FIREKNIVES_MAPPINGS->set_assassin_xcouncil_activity_cooldown(fist, 1);
		}
	}
	
	return;
}


int
no_boss()
{
	mixed arr;
	int i;
    
	arr = occ_fireknives_boss_list;
    
	if (!sizeof(arr))
	{
		return 1;
	}
    
	return 0;
}


int
no_fist()
{
	mixed arr;
	int i;
    
	arr = occ_fireknives_thefist_list;
    
	if (!sizeof(arr))
	{
		return 1;
	}
    
	return 0;
}


int
no_mentor()
{
	mixed arr;
	int i;
    
	arr = occ_fireknives_mentor_list;
    
	if (!sizeof(arr))
	{
		return 1;
	}
    
	return 0;
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    if (!restore_object(FIREKNIVES_SAVE_FILE))
    {
		occ_retired_council_list = ({});
		occ_fireknives_librarian_list = ({});
        occ_fireknives_list = ({});
        occ_fireknives_mentor_list = ({});
        occ_fireknives_thefist_list = ({});
        occ_fireknives_boss_list = ({});
        occ_fireknives_whisper_list = ({});
		guild_fullmember_list = ({});
		guild_trainee_list = ({});
        guild_enemy_list = ({});
        crow_list = ({});
    }
	
	//set_alarm(0.0, 7200.0, &activity_meter());
}