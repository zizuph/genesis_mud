#define SAVE_FILE "/d/Genesis/obj/gnome_deposit"

mapping accounts;

void
create()
{
    seteuid(getuid(this_object()));

    if(!restore_object(SAVE_FILE))
	accounts = ([ ]);
}

int *
query_account(string person)
{
    if (!accounts[person])
	return 0;
    else
	return accounts[person] + ({ });
}

void
set_account(string person, int *info)
{
    if (!sizeof(info))
	accounts = m_delete(accounts, person);
    else
	accounts[person] = info;
    save_object(SAVE_FILE);
}

string *
query_account_owners()
{
    return m_indexes(accounts);
}

int
remove_object()
{
    destruct();
    return 1;
}
