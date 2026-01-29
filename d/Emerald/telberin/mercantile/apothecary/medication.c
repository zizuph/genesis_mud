public string med_id = "";
public string med_desc = "";
public string med_name = "";

public nomask int
query_medication()
{
    return 1;
}

public void
set_medication_id(string id)
{
    med_id = id;
}

public string
query_medication_id()
{
    return med_id;
}

public void
set_medication_desc(string desc)
{
    med_desc = desc;
}

public string
query_medication_desc()
{
    return med_desc;
}

public void
set_medication_name(string name)
{
    med_name = name;
}

public string
query_medication_name()
{
    return med_name;
}
