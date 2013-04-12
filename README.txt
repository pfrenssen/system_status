-- SUMMARY --

System Status provides an easy way to get an overview of all the available
updates for your Drupal websites. Install System Status on all your Drupal
websites and allow reporting to DrupalStatus.org for a centralized overview
and email summaries of available updates and installed versions.

The accompanying service offered by DrupalStatus.org is free, but if you do not
want to use this service this lightweight module allows you to build your own
overviews and dashboard.
The idea is to offer a way to script something that can poll all of your sites
to check on modules and versions used, instead of having every Drupal site
check for updates separately (and using Update Manager.
This can be very useful in situations where you do not want to trust on the
update manager, or where your servers might not have the needed access to
check for updates.

The module allows administrators to build their own monitoring interface
to check on multiple installations at once.

This module WILL NOT check for updates. You will nead to create your own
service or to use Drupalstatus.org to generate reports and overviews.


-- REQUIREMENTS --

PHP 5.2.5 or higher (5.3 recommended)
mcrypt


-- INSTALLATION --

Project URL: http://drupal.org/project/system_status/
GitURL: git clone http://git.drupal.org:project/system_status.git
Download and install the module the same way you would download and
install other contributed modules.


-- INSTALLATION USING DRUSH --

drush dl system_status
drush en system_status


-- USAGE --

After installation go to the admin page under
/admin/config/system/system_status and allow reporting to DrupalStatus.org.