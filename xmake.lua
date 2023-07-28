add_rules("mode.debug", "mode.release")

if is_mode("debug") then
	add_defines("DEBUG")
	set_symbols("debug")
	set_warnings("all")
elseif is_mode("release") then
	set_strip("all")
end

add_syslinks("m")

target("objs")
	set_kind("object")
	set_warnings("all")
	add_includedirs("include")
	add_files("src/*.c")
	add_cflags("-fPIC")

target("radicalite")
	set_kind("static")
	set_warnings("all")
	add_includedirs("include")
	--add_files("src/*.c")
	add_deps("objs")
	set_basename("radical")
	set_prefixname("lib")


target("radicalite_shared")
	set_kind("shared")
	set_warnings("all")
	add_includedirs("include")
	--add_files("src/*.c")
	add_deps("objs")
	set_basename("radical")
	set_prefixname("lib")

target("headers")
	set_kind("headeronly")
	add_headerfiles("include/(*.h)") 
--local fs = os.filedirs("~/radicalite/*")
--print(fs[1])

local tests = {"eyyc", "xyline", "sin-cos", "eyyc_new", "simple_vector_calcs"}
if is_mode("debug") then
	table.insert(tests, "test")
end
for i,filename in pairs(tests) do
	target(filename)
		set_kind("binary")
		set_default(false)
		set_warnings("all")
		add_includedirs("include")
		add_deps("radicalite")
		add_rpathdirs(".")
		add_rpathdirs("/usr/lib")
		add_rpathdirs("/usr/local/lib")
		add_rpathdirs("@executable_path")
		add_files("examples/"..filename..".c")
end
