<?php

namespace Drupal\system_status\Access;

use Drupal\Core\Access\AccessCheckInterface;
use Drupal\Core\Session\AccountInterface;
use Symfony\Component\Routing\Route;
use Symfony\Component\HttpFoundation\Request;

class SystemStatusAccessCheck implements AccessCheckInterface {

  public function applies(Route $route) {
    return '_access_system_status_page';
  }
  
  public function access(Route $route, Request $request, AccountInterface $account) {
    // TODO: TOKEN CHECK
    //return static::DENY;  
    return static::ALLOW; 
  }
}
