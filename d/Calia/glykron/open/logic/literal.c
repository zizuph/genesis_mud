string atom_name;
status truth;

void set(string new_atom_name, status new_truth)
{
        atom_name = new_atom_name;
        truth = new_truth;
}

string query_atom_name(void)
{
    return atom_name;
}

status query_truth(void)
{
    return truth;
}
