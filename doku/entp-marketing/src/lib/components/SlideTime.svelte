<script lang="ts">
	import { slideTime } from '$lib/stores';

	const duration = 180;

	$: isNegative = $slideTime > duration;
	$: time = isNegative ? $slideTime - duration : duration - $slideTime;
	$: minutes = Math.floor(time / 60);
	$: seconds = time - minutes * 60;

	const p = (s) => s.toString().padStart(2, '0');
</script>

<span absolute right-5 top-5>{isNegative ? '-' : ''} {minutes}:{p(seconds)}</span>
