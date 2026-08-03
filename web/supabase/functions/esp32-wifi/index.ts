import { serve } from "https://deno.land/std@0.224.0/http/server.ts";

const corsHeaders = {
  "Access-Control-Allow-Origin": "*",
  "Access-Control-Allow-Headers": "authorization, x-client-info, apikey, content-type",
  "Access-Control-Allow-Methods": "GET, POST, OPTIONS",
};

serve(async (req) => {
  if (req.method === "OPTIONS") {
    return new Response("ok", { headers: corsHeaders });
  }

  if (req.method === "GET") {
    return json({
      ok: true,
      service: "esp32-wifi",
      message: "Supabase Edge Function is running.",
    });
  }

  if (req.method !== "POST") {
    return json({ ok: false, error: "Method not allowed" }, 405);
  }

  let body: Record<string, unknown>;

  try {
    body = await req.json();
  } catch {
    return json({ ok: false, error: "Invalid JSON body" }, 400);
  }

  const deviceId = body.deviceId;
  const ipAddress = body.ipAddress;
  const rssi = body.rssi;

  if (typeof deviceId !== "string" || deviceId.length === 0) {
    return json({ ok: false, error: "deviceId is required" }, 400);
  }

  return json({
    ok: true,
    receivedAt: new Date().toISOString(),
    deviceId,
    ipAddress,
    rssi,
  });
});

function json(data: unknown, status = 200) {
  return new Response(JSON.stringify(data), {
    status,
    headers: {
      ...corsHeaders,
      "Content-Type": "application/json",
    },
  });
}
