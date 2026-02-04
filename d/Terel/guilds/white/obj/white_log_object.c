#include "/d/Terel/include/Terel.h"
inherit "/std/object";

#define MEMBER_LOG  WHITE+"log/members"
#define ELDER_LOG WHITE+"log/elders"
#define LEADER_LOG WHITE+"log/leader"

string *mNames = ({});
string *eNames = ({});
string *lNames = ({});

int query_member(string name);
int query_elder(string name);
int query_leader(string name);


void
create_object()
{
    FIX_EUID;
    set_name("white_member_object");
    restore_object(MEMBER_LOG);
    restore_object(ELDER_LOG);
    restore_object(LEADER_LOG);
}

// Add a member

void
add_member(string name)
{
    if(query_member(name))
        return;
    mNames += ({ name });
    save_object(MEMBER_LOG);
}

// Add an Elder

void
add_elder(string name)
{
    if(query_elder(name))
        return;
    eNames += ({ name });
    save_object(MEMBER_LOG);
}

// Add a leader

void
add_leader(string name)
{
    if(query_leader(name))
        return;
    lNames += ({ name });
    save_object(MEMBER_LOG);
}

// Remove a member

void
remove_member(string name)
{
    mNames -= ({ name });
    save_object(MEMBER_LOG);
}

// Remove an elder

void
remove_elder(string name)
{
    eNames -= ({ name });
    save_object(MEMBER_LOG);
}

// Remove a leader

void
remove_leader(string name)
{
    lNames -= ({ name });
    save_object(MEMBER_LOG);
}

// Query is a member
int
query_member(string name)
{
    if(member_array(name, mNames) > -1)
        return 1;
    return 0;
}

// Query is an elder
int
query_elder(string name)
{
    if(member_array(name, eNames) > -1)
        return 1;
    return 0;
}

// Query is the leader
int
query_leader(string name)
{
    if(member_array(name, lNames) > -1)
        return 1;
    return 0;
}
