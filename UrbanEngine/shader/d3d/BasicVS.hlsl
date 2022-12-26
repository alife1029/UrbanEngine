struct VSOut
{
    float4 color : COLOR;
    float4 pos : SV_POSITION;
};

VSOut main(float3 pos : SV_POSITION, float4 color : COLOR)
{
    VSOut vso;

    vso.pos = float4(pos, 1.0f);
    vso.color = color;

    return vso;
}
