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
#include <composite.h>
#include <macros.h>
#include <std.h>
#include <mail.h>
#include "../guild.h";

void create();

// OCC vampires list
private string *occ_vampires_list = ({ });

// LAY vampires list
private string *lay_vampires_list = ({ });

// RACE vampires list
private string *race_vampires_list = ({ });

// Covens 
private string *coven1_list = ({ });
private string *coven1_master = ({ });
private string *coven1_mutiny_candidate = ({ });

private string *coven2_list = ({ });
private string *coven2_master = ({ });
private string *coven2_mutiny_candidate = ({ });

private string *coven3_list = ({ });
private string *coven3_master = ({ });
private string *coven3_mutiny_candidate = ({ });

private string *aging_check = ({ });

private string *nonxp_vamp = ({ });

private string *failed_vampire = ({ });

private string *vampire_progenitor = ({ });
private string *vampire_antediluvian = ({ });
private string *vampire_methuselah = ({ });
private string *vampire_elder = ({ });

int mut_test_int;


void remove_coven1_master(string name);
void remove_coven2_master(string name);
void remove_coven3_master(string name);


string
list_covenmaster1()
{
    string cmaster1;
    
	coven1_master = sort_array(coven1_master);
    
    for (int i = 0; i < sizeof(coven1_master); i++) 
    {
        if (i == 0)
        {
            cmaster1 = coven1_master[i];
        }
        
        if (i > 0)
        {
            cmaster1 = coven1_master[i];
        }
    }
    
    return cmaster1;
}


string
list_covenmaster2()
{
    string cmaster2;
    
	coven2_master = sort_array(coven2_master);
    
    for (int i = 0; i < sizeof(coven2_master); i++) 
    {
        if (i == 0)
        {
            cmaster2 = coven2_master[i];
        }
        
        if (i > 0)
        {
            cmaster2 = coven2_master[i];
        }
    }
    
    return cmaster2;
}


string
list_covenmaster3()
{
    string cmaster3;
    
	coven3_master = sort_array(coven3_master);
    
    for (int i = 0; i < sizeof(coven3_master); i++) 
    {
        if (i == 0)
        {
            cmaster3 = coven3_master[i];
        }
        
        if (i > 0)
        {
            cmaster3 = coven3_master[i];
        }
    }
    
    return cmaster3;
}


int
occ_vamp_members_check()
{
	mixed arr;

	arr = occ_vampires_list;
    
	return sizeof(arr);
}


int
occ_active_vamp_members_check()
{
    int active_vamps = 0;
    
    int gaug;
    
    occ_vampires_list = sort_array(occ_vampires_list);
    
    for (int i = 0; i < sizeof(occ_vampires_list); i++) 
    {
        gaug = VAMPIRES_MAPPINGS->query_thirst_gauge(occ_vampires_list[i]);
        
        if (gaug < 50)
        {
            active_vamps = active_vamps;
        }
        else
        {
            active_vamps = active_vamps +1;
        }
    }
    
	return active_vamps;
}


int
progenitor_check()
{
	mixed arr;

	arr = vampire_progenitor;
    
	return sizeof(arr);
}


int
antediluvian_check()
{
	mixed arr;

	arr = vampire_antediluvian;
    
	return sizeof(arr);
}


int
methuselah_check()
{
	mixed arr;

	arr = vampire_methuselah;
    
	return sizeof(arr);
}


int
elder_check()
{
	mixed arr;

	arr = vampire_elder;
    
	return sizeof(arr);
}


int
coven1_members_check()
{
	mixed arr;

	arr = coven1_list;
    
	return sizeof(arr);
}


int
coven2_members_check()
{
	mixed arr;

	arr = coven2_list;
    
	return sizeof(arr);
}


int
coven3_members_check()
{
	mixed arr;

	arr = coven3_list;
    
	return sizeof(arr);
}


int
coven1_mutineers_check()
{
	mixed arr;

	int i;
    
	arr = coven1_mutiny_candidate;
    
	return sizeof(arr);
}


int
coven2_mutineers_check()
{
	mixed arr;

	int i;
    
	arr = coven2_mutiny_candidate;
    
	return sizeof(arr);
}


int
coven3_mutineers_check()
{
	mixed arr;

	int i;
    
	arr = coven3_mutiny_candidate;
    
	return sizeof(arr);
}


void set_mut_test(int i)
{
    mut_test_int = i;
    
    return;
}


int query_mut_test()
{
    return mut_test_int;
}


int
coven_mutiny_checks()
{
    string cmas1;
    string cmas2;
    string cmas3;
    
    string mutname1;
    string mutname2;
    string mutname3;
       
    cmas1 = list_covenmaster1();
    cmas2 = list_covenmaster2();
    cmas3 = list_covenmaster3();
    
    int mutcheck1 = coven1_mutineers_check();
    int mutcheck2 = coven2_mutineers_check();
    int mutcheck3 = coven3_mutineers_check();
    
    int mcheck1 = coven1_members_check();
    int mcheck2 = coven2_members_check();
    int mcheck3 = coven3_members_check();
    
    int memcheck1 = coven1_members_check() / 2;
    int memcheck2 = coven2_members_check() / 2;
    int memcheck3 = coven3_members_check() / 2;

    if (cmas1 != 0)
    {
        if (mutcheck1 > memcheck1)
        {
            COVEN_LOG("coven_log",
            "The covenmaster " +cmas1+" was dethroned due to mutiny("
            +"Mutineers: "+mutcheck1+", Members: "+mcheck1+", coven 1)!\n");
            
            CREATE_MAIL("Removed as Covenmaster", "Vampires", cmas1, "",
            "The coven has rejected you as their covenmaster.");   

            remove_coven1_master(cmas1);

            coven1_mutiny_candidate = sort_array(coven1_mutiny_candidate);
            
            for (int i = 0; i < sizeof(coven1_mutiny_candidate); i++) 
            {
                mutname1 = coven1_mutiny_candidate[i];
 
                coven1_mutiny_candidate -= ({ mutname1 });
    
                sort_array(coven1_mutiny_candidate);
    
                save_object(VAMPIRES_SAVE_FILE);
            }
        }
    }
    
    if (cmas2 != 0)
    {
        if (mutcheck2 > memcheck2)
        {
            COVEN_LOG("coven_log",
            "The covenmaster " +cmas2+" was dethroned due to mutiny("
            +"Mutineers: "+mutcheck2+", Members: "+mcheck2+", coven 1)!\n"); 
            
            CREATE_MAIL("Removed as Covenmaster", "Vampires", cmas2, "",
            "The coven has rejected you as their covenmaster.");   

            remove_coven2_master(cmas2);

            coven2_mutiny_candidate = sort_array(coven2_mutiny_candidate);
            
            for (int i = 0; i < sizeof(coven2_mutiny_candidate); i++) 
            {
                mutname2 = coven2_mutiny_candidate[i];
 
                coven2_mutiny_candidate -= ({ mutname2 });
    
                sort_array(coven2_mutiny_candidate);
    
                save_object(VAMPIRES_SAVE_FILE);
            }            
                   
        }
    }
    
    if (cmas3 != 0)
    {
        if (mutcheck2 > memcheck3)
        {
            COVEN_LOG("coven_log",
            "The covenmaster " +cmas3+" was dethroned due to mutiny("
            +"Mutineers: "+mutcheck3+", Members: "+mcheck3+", coven 1)!\n");

            CREATE_MAIL("Removed as Covenmaster", "Vampires", cmas3, "",
            "The coven has rejected you as their covenmaster.");   

            remove_coven3_master(cmas3);

            coven3_mutiny_candidate = sort_array(coven3_mutiny_candidate);
            
            for (int i = 0; i < sizeof(coven3_mutiny_candidate); i++) 
            {
                mutname3 = coven3_mutiny_candidate[i];
 
                coven3_mutiny_candidate -= ({ mutname3 });
    
                sort_array(coven3_mutiny_candidate);
    
                save_object(VAMPIRES_SAVE_FILE);
            }                        
        }
    }
	      
	return 1;
}


int
is_mutiny_candidate1(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven1_mutiny_candidate) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_mutiny_candidate1(string name)
{  
    name = capitalize(name);
    
    if (is_mutiny_candidate1(name) == 1)
    {
        return;
    }

    coven1_mutiny_candidate += ({ name });
    
    sort_array(coven1_mutiny_candidate);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_mutiny_candidate1(string name)
{
    name = capitalize(name);

    if (is_mutiny_candidate1(name) != 1)
    {
        return;
    }
    
    coven1_mutiny_candidate -= ({ name });
    
    sort_array(coven1_mutiny_candidate);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_vamp_progenitor(string name)
{
    name = capitalize(name);
    
    if (member_array(name, vampire_progenitor) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_vamp_progenitor(string name)
{  
    name = capitalize(name);
    
    if (is_vamp_progenitor(name) == 1)
    {
        return;
    }

    vampire_progenitor += ({ name });
    
    sort_array(vampire_progenitor);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_vamp_progenitor(string name)
{
    name = capitalize(name);

    if (is_vamp_progenitor(name) != 1)
    {
        return;
    }
    
    vampire_progenitor -= ({ name });
    
    sort_array(vampire_progenitor);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_vamp_antediluvian(string name)
{
    name = capitalize(name);
    
    if (member_array(name, vampire_antediluvian) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_vamp_antediluvian(string name)
{  
    name = capitalize(name);
    
    if (is_vamp_antediluvian(name) == 1)
    {
        return;
    }

    vampire_antediluvian += ({ name });
    
    sort_array(vampire_antediluvian);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_vamp_antediluvian(string name)
{
    name = capitalize(name);

    if (is_vamp_antediluvian(name) != 1)
    {
        return;
    }
    
    vampire_antediluvian -= ({ name });
    
    sort_array(vampire_antediluvian);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_vamp_methuselah(string name)
{
    name = capitalize(name);
    
    if (member_array(name, vampire_methuselah) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_vamp_methuselah(string name)
{  
    name = capitalize(name);
    
    if (is_vamp_methuselah(name) == 1)
    {
        return;
    }

    vampire_methuselah += ({ name });
    
    sort_array(vampire_methuselah);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_vamp_methuselah(string name)
{
    name = capitalize(name);

    if (is_vamp_methuselah(name) != 1)
    {
        return;
    }
    
    vampire_methuselah -= ({ name });
    
    sort_array(vampire_methuselah);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}

int
is_vamp_elder(string name)
{
    name = capitalize(name);
    
    if (member_array(name, vampire_elder) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_vamp_elder(string name)
{  
    name = capitalize(name);
    
    if (is_vamp_elder(name) == 1)
    {
        return;
    }

    vampire_elder += ({ name });
    
    sort_array(vampire_elder);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_vamp_elder(string name)
{
    name = capitalize(name);

    if (is_vamp_elder(name) != 1)
    {
        return;
    }
    
    vampire_elder -= ({ name });
    
    sort_array(vampire_elder);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_mutiny_candidate2(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven2_mutiny_candidate) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_mutiny_candidate2(string name)
{  
    name = capitalize(name);
    
    if (is_mutiny_candidate2(name) == 1)
    {
        return;
    }

    coven2_mutiny_candidate += ({ name });
    
    sort_array(coven2_mutiny_candidate);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_mutiny_candidate2(string name)
{
    name = capitalize(name);

    if (is_mutiny_candidate2(name) != 1)
    {
        return;
    }
    
    coven2_mutiny_candidate -= ({ name });
    
    sort_array(coven2_mutiny_candidate);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_mutiny_candidate3(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven3_mutiny_candidate) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_mutiny_candidate3(string name)
{  
    name = capitalize(name);
    
    if (is_mutiny_candidate3(name) == 1)
    {
        return;
    }

    coven3_mutiny_candidate += ({ name });
    
    sort_array(coven3_mutiny_candidate);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_mutiny_candidate3(string name)
{
    name = capitalize(name);

    if (is_mutiny_candidate3(name) != 1)
    {
        return;
    }
    
    coven3_mutiny_candidate -= ({ name });
    
    sort_array(coven3_mutiny_candidate);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_failed_vampire(string name)
{
    name = capitalize(name);
    
    if (member_array(name, failed_vampire) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_failed_vampire(string name)
{  
    name = capitalize(name);
    
    if (is_failed_vampire(name) == 1)
    {
        return;
    }

    failed_vampire += ({ name });
    
    sort_array(failed_vampire);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_failed_vampire(string name)
{
    name = capitalize(name);

    if (is_failed_vampire(name) != 1)
    {
        return;
    }
    
    failed_vampire -= ({ name });
    
    sort_array(failed_vampire);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_nonxp_vampire(string name)
{
    name = capitalize(name);
    
    if (member_array(name, nonxp_vamp) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_nonxp_vampire(string name)
{  
    name = capitalize(name);
    
    if (is_nonxp_vampire(name) == 1)
    {
        return;
    }

    nonxp_vamp += ({ name });
    
    sort_array(nonxp_vamp);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_nonxp_vampire(string name)
{
    name = capitalize(name);

    if (is_nonxp_vampire(name) != 1)
    {
        return;
    }
    
    nonxp_vamp -= ({ name });
    
    sort_array(nonxp_vamp);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_aging_check(string name)
{
    name = capitalize(name);
    
    if (member_array(name, aging_check) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_aging_check(string name)
{  
    name = capitalize(name);
    
    if (is_aging_check(name) == 1)
    {
        return;
    }

    aging_check += ({ name });
    
    sort_array(aging_check);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_aging_check(string name)
{
    name = capitalize(name);

    if (is_aging_check(name) != 1)
    {
        return;
    }
    
    aging_check -= ({ name });
    
    sort_array(aging_check);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_coven1_member(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven1_list) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_coven1_member(string name)
{  
    name = capitalize(name);
    
    if (is_coven1_member(name) == 1)
    {
        return;
    }

    coven1_list += ({ name });
    
    sort_array(coven1_list);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_coven1_member(string name)
{
    name = capitalize(name);

    if (is_coven1_member(name) != 1)
    {
        return;
    }
    
    coven1_list -= ({ name });
    
    sort_array(coven1_list);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_coven1_master(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven1_master) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_coven1_master(string name)
{  
    name = capitalize(name);
    
    if (is_coven1_master(name) == 1)
    {
        return;
    }

    coven1_master += ({ name });
    
    sort_array(coven1_master);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_coven1_master(string name)
{
    name = capitalize(name);

    if (is_coven1_master(name) != 1)
    {
        return;
    }
    
    coven1_master -= ({ name });
    
    sort_array(coven1_master);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_coven2_member(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven2_list) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_coven2_member(string name)
{  
    name = capitalize(name);
    
    if (is_coven2_member(name) == 1)
    {
        return;
    }

    coven2_list += ({ name });
    
    sort_array(coven2_list);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_coven2_member(string name)
{
    name = capitalize(name);

    if (is_coven2_member(name) != 1)
    {
        return;
    }
    
    coven2_list -= ({ name });
    
    sort_array(coven2_list);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_coven2_master(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven2_master) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_coven2_master(string name)
{  
    name = capitalize(name);
    
    if (is_coven2_master(name) == 1)
    {
        return;
    }

    coven2_master += ({ name });
    
    sort_array(coven2_master);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_coven2_master(string name)
{
    name = capitalize(name);

    if (is_coven2_master(name) != 1)
    {
        return;
    }
    
    coven2_master -= ({ name });
    
    sort_array(coven2_master);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_coven3_member(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven3_list) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_coven3_member(string name)
{  
    name = capitalize(name);
    
    if (is_coven3_member(name) == 1)
    {
        return;
    }

    coven3_list += ({ name });
    
    sort_array(coven3_list);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_coven3_member(string name)
{
    name = capitalize(name);

    if (is_coven3_member(name) != 1)
    {
        return;
    }
    
    coven3_list -= ({ name });
    
    sort_array(coven3_list);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
is_coven3_master(string name)
{
    name = capitalize(name);
    
    if (member_array(name, coven3_master) != -1)
    {
        return 1;
    }
    
    return 0;
}


void
add_coven3_master(string name)
{  
    name = capitalize(name);
    
    if (is_coven3_master(name) == 1)
    {
        return;
    }

    coven3_master += ({ name });
    
    sort_array(coven3_master);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


void
remove_coven3_master(string name)
{
    name = capitalize(name);

    if (is_coven3_master(name) != 1)
    {
        return;
    }
    
    coven3_master -= ({ name });
    
    sort_array(coven3_master);
    
    save_object(VAMPIRES_SAVE_FILE);
    
    return;
}


int
no_coven1_master()
{
    mixed arr;
    int i;
    
    arr = coven1_master;
    
    if (!sizeof(arr))
    {
        return 1;
    }
    
    return 0;
}


int
no_coven2_master()
{
    mixed arr;
    int i;
    
    arr = coven2_master;
    
    if (!sizeof(arr))
    {
        return 1;
    }
    
    return 0;
}


int
no_coven3_master()
{
    mixed arr;
    int i;
    
    arr = coven3_master;
    
    if (!sizeof(arr))
    {
        return 1;
    }
    
    return 0;
}


int
is_occ_vampires(string name)
{
    name = capitalize(name);

    if (member_array(name, occ_vampires_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_occ_vampires(string name)
{  
    name = capitalize(name);

    if (is_occ_vampires(name) == 1)
    {
        return;
    }
    
    if (name == 0)
    {
        return;
    }

    occ_vampires_list += ({ name });

    sort_array(occ_vampires_list);
    
    save_object(VAMPIRES_SAVE_FILE);

    return;
}


void
remove_occ_vampires(string name)
{
    name = capitalize(name);

    if (is_occ_vampires(name) != 1)
    {
        return;
    }

    occ_vampires_list -= ({ name });
    
    sort_array(occ_vampires_list);

    save_object(VAMPIRES_SAVE_FILE);

    return;
}


int
is_lay_vampires(string name)
{
    name = capitalize(name);

    if (member_array(name, lay_vampires_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_lay_vampires(string name)
{  
    name = capitalize(name);

    if (is_lay_vampires(name) == 1)
    {
        return;
    }
    
    if (name == 0)
    {
        return;
    }

    lay_vampires_list += ({ name });

    sort_array(lay_vampires_list);
    
    save_object(VAMPIRES_SAVE_FILE);

    return;
}


void
remove_lay_vampires(string name)
{
    name = capitalize(name);

    if (is_lay_vampires(name) != 1)
    {
        return;
    }

    lay_vampires_list -= ({ name });
    
    sort_array(lay_vampires_list);

    save_object(VAMPIRES_SAVE_FILE);

    return;
}


int
is_race_vampires(string name)
{
    name = capitalize(name);

    if (member_array(name, race_vampires_list) != -1)
    {
        return 1;
    }

    return 0;
}


void
add_race_vampires(string name)
{  
    name = capitalize(name);

    if (is_race_vampires(name) == 1)
    {
        return;
    }
    
    if (name == 0)
    {
        return;
    }

    race_vampires_list += ({ name });

    sort_array(race_vampires_list);
    
    save_object(VAMPIRES_SAVE_FILE);

    return;
}


void
remove_race_vampires(string name)
{
    name = capitalize(name);

    if (is_race_vampires(name) != 1)
    {
        return;
    }

    race_vampires_list -= ({ name });
    
    sort_array(race_vampires_list);

    save_object(VAMPIRES_SAVE_FILE);

    return;
}


int set_vamp_abilities(string memb)
{
    // First vampire occ ability. Gets 1 immortalitypoint
    // that is handled by the evolve command. Cap: 1 imm point.
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(memb) >= VAMP_OCC_ABILITY_1)
    {
        if (!VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(memb))
        {
            int dice1 = 1 + random(2);
            
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_1(memb, dice1);
        }
    }
    
    // Second vampire occ ability. Gets 1 immortalitypoint
    //                             Cap: 3 imm point.
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(memb) >= VAMP_OCC_ABILITY_2)
    {
        if (!VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(memb))
        {
            int dice2 = 1 + random(2);
            int imm_points2;
            
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_2(memb, dice2);
 
            imm_points2 = VAMPIRES_MAPPINGS->query_vampires_resilience(memb);            
            imm_points2 = imm_points2 + 1;
            
            if (imm_points2 > 3)
            {
                imm_points2 = 3;
            }
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(memb, imm_points2);           
        }
    }
    
    // Third vampire occ ability. Gets 1 immortalitypoint
    //                            Cap: 5 imm point.
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(memb) >= VAMP_OCC_ABILITY_3)
    {
        if (!VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(memb))
        {
            int dice3 = 1 + random(2);
            int imm_points3;
            int agent;
            
            agent = random(10) + 1;
            
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_3(memb, dice3);
            
            imm_points3 = VAMPIRES_MAPPINGS->query_vampires_resilience(memb);            
            imm_points3 = imm_points3 + 1;
            
            if (imm_points3 > 5)
            {
                imm_points3 = 5;
            }
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(memb, imm_points3); 

            VAMPIRES_MAPPINGS->set_vamp_agent(memb, agent);            
        }
    }

    // Fourth vampire occ ability. Gets 1 immortalitypoint
    //                             Cap: 7 imm point.
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(memb) >= VAMP_OCC_ABILITY_4)
    {
        if (!VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(memb))
        {
            int dice4 = 1 + random(2);
            int imm_points4;
            
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_4(memb, dice4);
            
            imm_points4 = VAMPIRES_MAPPINGS->query_vampires_resilience(memb);            
            imm_points4 = imm_points4 + 1;
            
            if (imm_points4 > 7)
            {
                imm_points4 = 7;
            }
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(memb, imm_points4);    
        }
    }
    
    // Elder vampire tier. Gets 1 immortalitypoint
    //                            Cap: 9 imm point.
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(memb) >= VAMP_OCC_ABILITY_5)
    {
        if (!VAMPIRES_MAPPINGS->query_vampire_ability_occ_5(memb))
        {
            int dice5 = 1;
            int imm_points5;
            
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_5(memb, dice5);
            
            imm_points5 = VAMPIRES_MAPPINGS->query_vampires_resilience(memb);            
            imm_points5 = imm_points5 + 1;
            
            if (imm_points5 > 9)
            {
                imm_points5 = 9;
            }
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(memb, imm_points5);    
        }
    }
    
    // Sixt vampire tier. Methusela flagging
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(memb) >= VAMP_OCC_ABILITY_6)
    {
        if (!VAMPIRES_MAPPINGS->query_vampire_ability_occ_6(memb))
        {
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_6(memb, 1); 
        }
    }
    
    // Seventht vampire tier. Antediluvian flagging
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(memb) >= VAMP_OCC_ABILITY_7)
    {
        if (!VAMPIRES_MAPPINGS->query_vampire_ability_occ_7(memb))
        {
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_7(memb, 1); 
        }
    }
    
    // Eighth vampire tier. Progenitor flagging
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(memb) >= VAMP_OCC_ABILITY_8)
    {
        if (!VAMPIRES_MAPPINGS->query_vampire_ability_occ_8(memb))
        {
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_8(memb, 1); 
        }
    }

    // Progenitor
    if (VAMPIRES_MAPPINGS->query_vampires_progenitor(this_player()->query_real_name()) == 1)
    {
        // TODO
        
        return 1;
    }
}


int
guild_members_age_gauge_increase()
{
    string member;
    
    int member_gauge, member_thirst;
    
    // To age, a vampire must have this factor in
    // percent 
    int percent_factor = 90;
    
    int vampirespawn_countdwn;
    
    lay_vampires_list = sort_array(lay_vampires_list);
    
    for (int i = 0; i < sizeof(lay_vampires_list); i++) 
    {
        member = lay_vampires_list[i];

        member_thirst = VAMPIRES_MAPPINGS->query_thirst_gauge(member);
        
        member_gauge = VAMPIRES_MAPPINGS->query_vampires_gauge(member);
        
        // Too thirsty vampires won't benefit from time growth, therefore
        // a minimum requirement of thirst is necessary for them to
        // gain time points.
        
        int min_age;
        
        // If age is less than 1450
        switch(member_gauge)
        {
            //////////// VAMPIRE SPAWNS BELOW ///////////
            
            // Over 12 blood to grow
            case 0..24:
            min_age = 12;
            break;
            
            // Over 28 blood to grow
            case 25..48:
            min_age = 28;
            break;
            
            // Over 44 blood to grow
            case 49..72:
            min_age = 44;
            break;
            
            // Over 70 blood to grow
            case 73..100:
            min_age = 70;
            break;
            
            // Over 105 blood to grow
            case 101..250:
            min_age = 105;
            break;
            
            // Over 160 blood to grow
            case 251..500:
            min_age = 160;
            break;
            
            // Over 200 blood to grow
            case 501..1000:
            min_age = 200;
            break;
            
            // Over 240 blood to grow
            case 1001..1440:
            min_age = 240;
            break;

            // Over 280 blood to grow
            case 1441..1450:
            min_age = 280;
            break;
   
   
            //////////// FULL VAMPIRES BELOW ///////////
          
            // Over 320 blood to grow
            // Bloodcap at 400
            // 80 difference
            case 1451..2000:
            min_age = 320;
            break;
            
            // Over 360 blood to grow
            // Bloodcap at 450
            // 90 difference
            case 2001..3000:
            min_age = 360;
            break;
            
            // Over 400 blood to grow
            // Bloodcap at 500
            // 100 difference
            case 3001..5000:
            min_age = 400;
            break;
            
            // Over 450 blood to grow
            // Bloodcap at 550
            // 100 difference
            case 5001..7000:
            min_age = 450;
            break;
            
            // Over 500 blood to grow
            // Bloodcap at 600
            // 100 difference
            case 7001..9000:
            min_age = 500;
            break;
            
            // Over 600 blood to grow
            // Bloodcap at 700
            // 100 difference
            case 9001..11000:
            min_age = 600;
            break;
            
            // Over 700 blood to grow
            // Bloodcap at 800
            // 100 difference
            case 11001..13000:
            min_age = 700;
            break;
            
            // Over 800 blood to grow
            // Bloodcap at 900
            // 100 difference
            case 13001..15000:
            min_age = 800;
            break;
            
            // Over 900 blood to grow
            // Bloodcap at 1000
            // 100 difference
            case 15001..17000:
            min_age = 900;
            break;
            
            // Over 1000 blood to grow
            // Bloodcap at 1200
            // 200 difference
            case 17001..23000:
            min_age = 1000;
            break;
        }
        
        // If the current thirst is at percentfactor or above the 
        // current agecap for the vampire, the vampire
        // will age. Else, he will not.
        if (member_thirst > min_age)
        {
            // Vampires flagged for nonaging due to other reasons.
            if (VAMPIRES_MASTER->is_aging_check(member))
            {
                member_gauge = member_gauge;
            }
            else
            {
                member_gauge = member_gauge +1;
            }          
        }
        
        // Non OCC members caps at 1450 in age, and is subject to
        // guildkick if the countdowntimer is higher than the age
        // gauge.        
        if (VAMPIRES_MASTER->is_occ_vampires(member) == 0)
        {
            // 1450 hours, 2 months + 10 hours = cap.
            if (member_gauge >= 1450)
            {
                member_gauge = 1450;
            }
            
            vampirespawn_countdwn = VAMPIRES_MAPPINGS->query_vampirespawn_timer(member);
            
            
            // Time is up. Vorador remove spawns that hasn't evolved yet.
            /*if (vampirespawn_countdwn == 1450)
            {
                VAMPIRES_MASTER->remove_lay_vampires(member);
                
                LEAVE_LOG("leave_log",
                "The Vampire Spawn " +member 
                +" is flagged for removal due to inactivity.\n");
                
                return 1;
            }*/
            
            // Activity is too low - member removed, freeing up a spawn slot
            if (vampirespawn_countdwn >= member_gauge)
            {   
                if (VAMPIRES_MASTER->is_failed_vampire(member) == 0)
                {
                    VAMPIRES_MASTER->add_failed_vampire(member);
            
                    LEAVE_LOG("leave_log",
                    "The Vampire Spawn " +member 
                    +" is flagged for removal due to inactivity.\n");
                    
                    CREATE_MAIL("Destruction", "Vampires", member, "",
                    "Vorador has removed you from his pool of vampire "
                    +"spawns due to low activity.\n");                           
                }
            }          
        }
        
        // Vampires with no reputation and no vampire nation standing will
        // linger right under Vampire Lord status
        /*if (member_gauge >= 10998)
        {
            int xtest = VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name());
            
            //if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) < 20)
            /*if (xtest < 20)
            {
                member_gauge = 10998;          
            }*/
            
            /*if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) < 20)
            {
                member_gauge = 10998;
            }
        }
        
        
        // Vampires with under req reputation and vampire nation standing will
        // linger right under Elder vampire status
        if (member_gauge >= 12998)
        {
            if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) < 40)
            {
                member_gauge = 12998;          
            }
            
            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) < 40)
            {
                member_gauge = 12998;
            }
        }
        
        // Vampires with under req reputation and vampire nation standing will
        // linger right under Methuselah vampire status
        if (member_gauge >= 14998)
        {
            if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) < 60)
            {
                member_gauge = 14998;          
            }
            
            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) < 60)
            {
                member_gauge = 14998;
            }
        }
        
        // Vampires with under req reputation and vampire nation standing will
        // linger right under Antediluvian vampire status
        if (member_gauge >= 16998)
        {
            if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) < 80)
            {
                member_gauge = 16998;          
            }
            
            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) < 80)
            {
                member_gauge = 16998;
            }
        }
        
        // Vampires with under req reputation and vampire nation standing will
        // linger right under Progenitor vampire status
        if (member_gauge >= 21998)
        {
            if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) < 100)
            {
                member_gauge = 21998;          
            }
            
            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) < 100)
            {
                member_gauge = 21998;
            }
        }*/

        // Cap is at about 2 years of continued activity
        // for OCC vampires
        if (member_gauge >= 22010)
        {
            member_gauge = 220010;
        }
        
        if (VAMPIRES_MASTER->is_failed_vampire(member) == 0)
        {
            int currage = VAMPIRES_MAPPINGS->query_vampires_gauge(member);
            
            if (currage < member_gauge)
            {
                AGE_GAUGE_LOG("age_log",
                "The Vampire (Spawn) " +member 
                +" aged 1 point.\n");
            }
                       
            VAMPIRES_MAPPINGS->set_vampires_gauge(member, member_gauge);
            
            set_vamp_abilities(member);
        }     
    }
        
    return 1;
}


int
guild_members_thirstmeter()
{
    string member;
    int member_thirst;

    lay_vampires_list = sort_array(lay_vampires_list);

    for (int i = 0; i < sizeof(lay_vampires_list); i++) 
    {
        member = lay_vampires_list[i];

        member_thirst = VAMPIRES_MAPPINGS->query_thirst_gauge(member);
        member_thirst = member_thirst -1;
        
        if (member_thirst <= 1)
        {
            member_thirst = 1;
        }
        
        VAMPIRES_MAPPINGS->set_thirst_gauge(member, member_thirst);
    }
    
    return 1;
}


int
vampirespawn_countdown()
{
    string member;

    int vampirespawn_countdown;
    
    int vamp_b;
    
    int member_gauge;

    lay_vampires_list = sort_array(lay_vampires_list);

    for (int i = 0; i < sizeof(lay_vampires_list); i++) 
    {
        member = lay_vampires_list[i];

        vamp_b = VAMPIRES_MAPPINGS->query_vamp_blessed(member);
        vampirespawn_countdown = VAMPIRES_MAPPINGS->query_vampirespawn_timer(member);
        vampirespawn_countdown = vampirespawn_countdown + 1;
        
        member_gauge = VAMPIRES_MAPPINGS->query_vampires_gauge(member);
        
        if (vampirespawn_countdown >= 1448)
        {
            vampirespawn_countdown = 1448;
        }
        
        if (VAMPIRES_MASTER->is_occ_vampires(member) == 1)
        {
            vampirespawn_countdown = 1;
        }
        
        if (vamp_b == 1)
        {
            vampirespawn_countdown = 1;
        }
        
        if (member_gauge >= 1449)
        {
            vampirespawn_countdown = 1;
        }
        
        
        VAMPIRES_MAPPINGS->set_vampirespawn_timer(member, vampirespawn_countdown);
    }
    
    return 1;
}


/*int
query_mutiny_coven1()
{
    return coven1_mutiny;
}


int
query_mutiny_coven2()
{
    return coven2_mutiny;
}


int
query_mutiny_coven3()
{
    return coven3_mutiny;
}*/


/*int
mutiny_update()
{
    int total_m1;
    int total_m2;
    int total_m3;

    coven1_mutiny = sort_array(coven1_mutiny_candidate);
    coven2_mutiny = sort_array(coven2_mutiny_candidate);
    coven3_mutiny = sort_array(coven3_mutiny_candidate);

    for (int i = 0; i < sizeof(coven1_mutiny_candidate); i++) 
    {
        total_m1 = total_m1 + 1;
    }
    
    for (int i = 0; i < sizeof(coven2_mutiny_candidate); i++) 
    {
        total_m2 = total_m1 + 1;
    }
    
    for (int i = 0; i < sizeof(coven3_mutiny_candidate); i++) 
    {
        total_m3 = total_m1 + 1;
    }
    
    return 1;
}*/


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    if (!restore_object(VAMPIRES_SAVE_FILE))
    {
        occ_vampires_list = ({});
        lay_vampires_list = ({});
        race_vampires_list = ({});
        
        coven1_list = ({});
        coven1_master = ({});
        coven1_mutiny_candidate = ({});

        coven2_list = ({});
        coven2_master = ({});
        coven2_mutiny_candidate = ({});

        coven3_list = ({});
        coven3_master = ({});
        coven3_mutiny_candidate = ({});
        
        aging_check = ({});
        
        nonxp_vamp = ({});
        
        failed_vampire = ({});
        
        vampire_progenitor = ({});
        vampire_antediluvian = ({});
        vampire_methuselah = ({});
        vampire_elder = ({});
    }
      
    // Activity increases once per hour.
    set_alarm(3600.0, 3600.0, &guild_members_age_gauge_increase());
    
    // Countdown increases 1 point per 2 hours.
    set_alarm(7200.0, 7200.0, &vampirespawn_countdown());
     
    // Blood drops 1 point every 30 minutes. (48 per 24 hours)
    set_alarm(1800.0, 1800.0, &guild_members_thirstmeter());
    
    // mutiny_checks.
    set_alarm(30.0, 3600.0, &coven_mutiny_checks());
}