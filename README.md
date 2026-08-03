# guswo

ESP32 Arduino code and Supabase Edge Functions for ESP32 Wi-Fi/API integration.

## Environment

Copy `.env.example` to `.env`, then fill in your own values.

```powershell
Copy-Item .env.example .env
```

Do not commit `.env`.

For ESP32 uploads, copy the example secrets header and fill in local values.

```powershell
Copy-Item esp32/esp32_wifi_supabase/secrets.example.h esp32/esp32_wifi_supabase/secrets.h
```

Do not commit `secrets.h`.

## Supabase CLI

The Supabase folder is located at:

```text
web/supabase
```

After filling `.env`, the Edge Function can be deployed with the Supabase CLI.
