
-- SUMMARY --

System Status is a very lightweight module that gives a simple overview of
current used modules and their version. This would allow administrators to
build their own monitoring interface to check on multiple installations at 
once.

This module will NOT check for updates.

In time this module will not only serve 'pull' request but will also have 
the possibility to inform by itself using webcalls or syslog or ...


-- REQUIREMENTS --

None.


-- INSTALLATION --

Project URL: http://drupal.org/project/system_status/
GitURL: git clone http://git.drupal.org:project/system_status.git

Download and install the module normally as you would install other 
contributed module.


-- USAGE --

After installation go to the admin page under 
/admin/config/system/system_status and allow public calls. 
(The default entered IP address should work fine)

Once you saved the settings you should be able to: 
GET $base_url/admin/reports/system_status  
(ex. http://www.my-site.com/admin/reports/system_status ) 
