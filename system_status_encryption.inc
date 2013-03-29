<?php
/**
 * @file
 * Encryption logic for system_status
 */

class SystemStatusEncryption {

  public static function getToken() {
    $chars = array_merge(range(0, 9),
      range('a', 'z'),
      range('A', 'Z'),
      range(0,99));

    shuffle($chars);

    $token = "";
    for($i=0; $i<8; $i++) {
      $token .= $chars[$i];
    }

    return $token;
  }
}
