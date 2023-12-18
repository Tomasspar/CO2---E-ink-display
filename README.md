# CO2---E-ink-display

## CO2-firmware
Kods tika izmantots priekš autonomas CO2 gaisa kvalitātes mērījumu veikšanas. Iekārta darbojās izmantojot 5v USB barošanu, ESP32-C3-mini mikroprocesoru un SCD41 sensoru. Sakarā ar iekārtas mazajiem izmēriem, bija problēmas ar paaugstinātiem temperatūras mērījumiem kuri bija saistīti ar ESP32-C3-mini silšanu. Tāpēc mikroprocesors veica iemigšanas un pamošanās procedūras, lai samazinātu patērēto jaudu.
Iekārta veica mērījumus ik pēc 3 minūtēm. Kad mērījumi tika nolasīti, iekārta pieslēdzās lokālajam Wi-Fi tīklam un augšupielādēja datus serverī. Pats lietotājs, ar telefona aplikācijas palīdzību, varēja sekot līdzi gaisa kvalitātes mērījumiem no jebkuras vietas pasaulē. Vēl ir ieviesta Bluetooth funkcionalitāte, kur lietotājs caur aplikāciju varētu ievadīt Wi-Fi tīkla nosaukumu un paroli, lai iekārta varētu pieslēgties pie servera.
Ir ieviesta OTA (over the air update)

## E-ink display (pārējie faili)
Bezvadu (lādējams) E-ink displejs, kas pieslēdzoties pie servera var nolasīt pēdējos CO2 iekārtu mērījumus un attēlot tos uz ekrāna, neatkarīgi kur pašas iekārtas atrodas. Arī šī iekārta izmantoja ESP32-C3-mini mikroprocesoru.
