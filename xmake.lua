if is_mode("debug") then
    add_defines("DEBUG")
    set_symbols("debug")
elseif is_mode("release") then
end

target("radicalite")
    set_kind("static")
	set_warnings("all")
    add_includedirs("include")
    add_files("src/*.c")
	set_basename("radicalite")

target("radicalite_shared")
	set_kind("shared")
	set_warnings("all")
	add_includedirs("include")
	add_files("src/*.c")
	set_basename("radicalite")

local tests = {"eyyc", "xyline", "sin-cos", "eyyc_new", "simple_vector_calcs"}
if is_mode("debug") then
	table.insert(tests, "test")
end
for i,filename in pairs(tests) do
	target(filename)
		set_kind("binary")
		set_warnings("all")
		add_includedirs("include")
		add_deps("radicalite")
		add_rpathdirs(".")
		add_files("examples/"..filename..".c")
end
