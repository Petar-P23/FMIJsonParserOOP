# FMIJsonParserOOP
How to use:
1. Load json file. e.g. -> select 0 -> test.json -> enter key
2. All paths should assume root location.
3. Consider the following json: 
{  
    "employee": {  
        "name":       "sonoo",   
        "salary":      56000,   
        "married":    true  
    }  
}  

Path to variable name should be employee/name

4. If moving, all paths that do not exist will be created (object type is assumed)

Moving "employee/name" to "new" would change the json as such:

{
        "employee" : {
                "salary" : 56000,
                "married" : true
                },
        "new" : {
                "name" :"sonoo"
                }
} 

5. All json files should follow the format as the example json
