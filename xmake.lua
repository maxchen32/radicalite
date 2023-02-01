if is_mode("debug") then
    add_defines("DEBUG")
    set_symbols("debug")
elseif is_mode("release") then
end

target("radicalite") 
    set_kind("static")
    add_includedirs("include")
    add_files("src/*.c")
	set_basename("libradicalite")

target("radicalite_shared")
	set_kind("shared")
	add_includedirs("include")
	add_files("src/*.c")
	set_basename("libradicalite")

local tests = {"eyyc", "xyline", "sin-cos", "eyyc_new"}
if is_mode("debug") then
	table.insert(tests, "test")
end
for i,filename in pairs(tests) do
	target(filename)
		set_kind("binary")
		add_includedirs("include")
		add_files("examples/"..filename..".c")
		add_deps("radicalite")
end
