void Display_one(void) {

  clearArray();
  statusBar();




  /*
 temp_1 = 20;
 hum_1 = 40;
 ppm_1 = 555;
*/
  int spacing = 30;
  int space = 3;

  int number = ppm_1;
  int digits = 0;

  if (up_to_date_1 == 0) {
    addElement(121, 185, 8);
  }

  if (name_1 != "") {
    writeText(name_1, spacing, 50, 1);
  }


  int tem = ppm_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  int ppmArray[digits];

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    ppmArray[i] = remainder;
  }

  int posY = 143;

  for (int i = digits - 1; i >= 0; i--) {
    switch (ppmArray[i]) {
      case 0:
        addElement(0, spacing, posY);
        spacing += 39;
        spacing += 5;
        break;
      case 1:
        addElement(1, spacing, posY);
        spacing += 26;
        spacing += 5;
        break;
      case 2:
        addElement(2, spacing, posY);
        spacing += 38;
        spacing += 5;
        break;
      case 3:
        addElement(3, spacing, posY);
        spacing += 38;
        spacing += 5;
        break;
      case 4:
        addElement(4, spacing, posY);
        spacing += 46;
        spacing += 5;
        break;
      case 5:
        addElement(5, spacing, posY);
        spacing += 39;
        spacing += 5;
        break;
      case 6:
        addElement(6, spacing, posY);
        spacing += 39;
        spacing += 5;
        break;
      case 7:
        addElement(7, spacing, posY);
        spacing += 37;
        spacing += 5;
        break;
      case 8:
        addElement(8, spacing, posY);
        spacing += 39;
        spacing += 5;
        break;
      case 9:
        addElement(9, spacing, posY);
        spacing += 39;
        spacing += 5;
        break;
      default:
        // statements
        break;
    }
  }



  addElement(123, 34, 265);
  addElement(124, 172, 265);
  addElement(125, 338, 265);

  int triangle_x = 42;
  //335

  if (ppm_1 <= 400) {


  } else if (ppm_1 > 1200) {

    triangle_x = 338;

  } else if (ppm_1 >= 400 && ppm_1 <= 800) {
    //135
    triangle_x += (ppm_1 - 400) / 3;

  } else if (ppm_1 > 800 && ppm_1 <= 1000) {
    //100
    triangle_x = 135;
    triangle_x += (ppm_1 - 800) / 2;

  } else if (ppm_1 > 1000 && ppm_1 <= 1200) {
    //100
    triangle_x = 235;
    triangle_x += (ppm_1 - 1000) / 2;
  }


  posY = 98;
  //PPM
  addElement(41, 30, posY);

  posY = 83;
  //Cloud
  addElement(42, 100, posY);

  //triangle
  addElement(27, triangle_x, 233);

  //line
  addElement(28, 50, 250);


  bool negative = false;

  if (temp_1 < 0) {
    negative = true;
    temp_1 = temp_1 * (-1);
  }

  spacing = 285;
  int digit = (int)((temp_1 - (int)temp_1) * 10);

  posY = 95;

  switch (digit) {
    case 0:
      spacing -= 19;
      addElement(10, spacing, posY);
      spacing -= space;
      break;
    case 1:
      spacing -= 13;
      addElement(11, spacing, posY);
      spacing -= space;
      break;
    case 2:
      spacing -= 18;
      addElement(12, spacing, posY);
      spacing -= space;
      break;
    case 3:
      spacing -= 19;
      addElement(13, spacing, posY);
      spacing -= space;
      break;
    case 4:
      spacing -= 22;
      addElement(14, spacing, posY);
      spacing -= space;
      break;
    case 5:
      spacing -= 18;
      addElement(15, spacing, posY);
      spacing -= space;
      break;
    case 6:
      spacing -= 19;
      addElement(16, spacing, posY);
      spacing -= 5;
      break;
    case 7:
      spacing -= 18;
      addElement(17, spacing, posY);
      spacing -= space;
      break;
    case 8:
      spacing -= 19;
      addElement(18, spacing, posY);
      spacing -= space;
      break;
    case 9:
      spacing -= 19;
      addElement(19, spacing, posY);
      spacing -= space;
      break;
    default:
      // statements
      break;
  }

  posY = 125;

  spacing -= 7;
  //dot
  addElement(20, spacing, posY);
  spacing -= space;

  number = temp_1;
  digits = 0;
  tem = temp_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }

  posY = 95;

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    switch (remainder) {
      case 0:
        spacing -= 19;
        addElement(10, spacing, posY);
        spacing -= space;
        break;
      case 1:
        spacing -= 13;
        addElement(11, spacing, posY);
        spacing -= space;
        break;
      case 2:
        spacing -= 18;
        addElement(12, spacing, posY);
        spacing -= space;
        break;
      case 3:
        spacing -= 13;
        addElement(13, spacing, posY);
        spacing -= space;
        break;
      case 4:
        spacing -= 22;
        addElement(14, spacing, posY);
        spacing -= space;
        break;
      case 5:
        spacing -= 18;
        addElement(15, spacing, posY);
        spacing -= space;
        break;
      case 6:
        spacing -= 19;
        addElement(16, spacing, posY);
        spacing -= 5;
        break;
      case 7:
        spacing -= 18;
        addElement(17, spacing, posY);
        spacing -= space;
        break;
      case 8:
        spacing -= 19;
        addElement(18, spacing, posY);
        spacing -= space;
        break;
      case 9:
        spacing -= 19;
        addElement(19, spacing, posY);
        spacing -= space;
        break;
      default:
        // statements
        break;
    }
  }


  if (negative) {
    addElement(116, spacing - 12, posY + 18);
  }


  posY = 93;

  //temperature
  addElement(23, 350, posY);


  posY = 95;

  bool m = preferences.getBool("metric", true);

  if (m) {
    //C
    addElement(21, 311, posY);
  } else {
    //F
    addElement(22, 311, posY);
  }


  //degree
  addElement(26, 291, posY);






  number = hum_1;
  digits = 0;
  tem = hum_1;  // create a temporary variable to avoid changing the original number
  while (tem != 0) {
    digits++;   // increment the digit count
    tem /= 10;  // remove the rightmost digit
  }


  spacing = 285;

  posY = 167;

  for (int i = 0; i < digits; i++) {
    int remainder = number % 10;
    number /= 10;
    number += remainder * pow(10, digits - 1);
    switch (remainder) {
      case 0:
        spacing -= 19;
        addElement(10, spacing, posY);
        spacing -= space;
        break;
      case 1:
        spacing -= 13;
        addElement(11, spacing, posY);
        spacing -= space;
        break;
      case 2:
        spacing -= 18;
        addElement(12, spacing, posY);
        spacing -= space;
        break;
      case 3:
        spacing -= 19;
        addElement(13, spacing, posY);
        spacing -= space;
        break;
      case 4:
        spacing -= 22;
        addElement(14, spacing, posY);
        spacing -= space;
        break;
      case 5:
        spacing -= 18;
        addElement(15, spacing, posY);
        spacing -= space;
        break;
      case 6:
        spacing -= 19;
        addElement(16, spacing, posY);
        spacing -= space;
        break;
      case 7:
        spacing -= 18;
        addElement(17, spacing, posY);
        spacing -= 5;
        break;
      case 8:
        spacing -= 19;
        addElement(18, spacing, posY);
        spacing -= space;
        break;
      case 9:
        spacing -= 19;
        addElement(19, spacing, posY);
        spacing -= space;
        break;
      default:
        // statements
        break;
    }
  }

  posY = 165;
  //humidity
  addElement(24, 347, posY);

  posY = 167;
  //percentage
  addElement(25, 295, posY);



  // draw();
}
